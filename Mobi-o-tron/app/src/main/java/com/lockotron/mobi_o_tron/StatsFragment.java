package com.lockotron.mobi_o_tron;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceActivity;
import android.support.annotation.Nullable;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.support.v7.widget.AppCompatSpinner;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Toast;

import com.lockotron.mobi_o_tron.exception.ServerNotSetException;
import com.lockotron.mobi_o_tron.model.Usuario;
import com.lockotron.mobi_o_tron.util.Statistics;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


/**
 * A simple {@link Fragment} subclass.
 * Activities that contain this fragment must implement the
 * {@link StatsFragment.OnFragmentInteractionListener} interface
 * to handle interaction events.
 * Use the {@link StatsFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class StatsFragment extends Fragment {
    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";
    private static final String TAG = "MOBI-O-TRON";

    // TODO: Rename and change types of parameters
    private String mParam1;
    private String mParam2;

    private OnFragmentInteractionListener mListener;
    private Snackbar serverNotSetSnackbar;
    private Snackbar serverErrorSnackbar;
    private List<Usuario> mUsersList = new ArrayList<>();
    private UsersAdapter mUsersAdapter;

    public StatsFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment StatsFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static StatsFragment newInstance(String param1, String param2) {
        StatsFragment fragment = new StatsFragment();
        Bundle args = new Bundle();
        args.putString(ARG_PARAM1, param1);
        args.putString(ARG_PARAM2, param2);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (getArguments() != null) {
            mParam1 = getArguments().getString(ARG_PARAM1);
            mParam2 = getArguments().getString(ARG_PARAM2);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_stats, container, false);
    }

    // TODO: Rename method, update argument and hook method into UI event
    public void onButtonPressed(Uri uri) {
        if (mListener != null) {
            mListener.onFragmentInteraction(uri);
        }
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        // snackbar que mostra erro caso servidor não tenha sido definido
        serverNotSetSnackbar = Snackbar.make(getView(), ServerNotSetException.PUBLIC_ERROR_MESSAGE, Snackbar.LENGTH_INDEFINITE);
        serverNotSetSnackbar.setAction(R.string.snackbar_action_settings, new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getActivity(), SettingsActivity.class);
                intent.putExtra(PreferenceActivity.EXTRA_SHOW_FRAGMENT, SettingsActivity.GeneralPreferenceFragment.class.getName());
                intent.putExtra(PreferenceActivity.EXTRA_NO_HEADERS, true);
                startActivity(intent);
            }
        });

        serverErrorSnackbar = Snackbar.make(getView(), R.string.error_server_generic, Snackbar.LENGTH_LONG);

        mUsersAdapter = new UsersAdapter(getContext(), mUsersList);

        AppCompatSpinner spinner = (AppCompatSpinner) getView().findViewById(R.id.user);
        spinner.setAdapter(mUsersAdapter);

        refresh(getActivity());
    }

    void refresh(Activity activity) {
        // Atualiza a lista de usuarios
        GetUsersTask getLogTask = new GetUsersTask();
        getLogTask.execute(activity);


        //TODO: Enviar usuários do log
        Usuario mostFrequentUser = Statistics.mostFrequentUser(activity, Arrays.asList(new Usuario(2, "Fulano"), new Usuario(3, "Rodrigo"), new Usuario(1, "Rafael"), new Usuario(3, "Rodrigo")));
        Toast.makeText(activity, mostFrequentUser.getNome(), Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        if (context instanceof OnFragmentInteractionListener) {
            mListener = (OnFragmentInteractionListener) context;
        } else {
            throw new RuntimeException(context.toString()
                    + " must implement OnFragmentInteractionListener");
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }

    /**
     * This interface must be implemented by activities that contain this
     * fragment to allow an interaction in this fragment to be communicated
     * to the activity and potentially other fragments contained in that
     * activity.
     * <p/>
     * See the Android Training lesson <a href=
     * "http://developer.android.com/training/basics/fragments/communicating.html"
     * >Communicating with Other Fragments</a> for more information.
     */
    public interface OnFragmentInteractionListener {
        // TODO: Update argument type and name
        void onFragmentInteraction(Uri uri);
    }

    class UsersAdapter extends ArrayAdapter<Usuario>{
        private final Context context;
        private final List<Usuario> users;

        public UsersAdapter(Context context, List<Usuario> users) {
            super(context, android.R.layout.simple_list_item_1, android.R.id.text1, users);
            this.context = context;
            this.users = users;
        }

        @Override
        public int getCount() {
            return users.size();
        }

        @Override
        public Usuario getItem(int position) {
            return users.get(position);
        }

        @Override
        public long getItemId(int position) {
            return users.get(position).getId();
        }
    }

    class GetUsersTask extends AsyncTask<Context, Void, Void> {

        @Override
        protected void onPreExecute() {
        }

        @Override
        protected Void doInBackground(Context... contexts) {
            try {
                mUsersList.clear();
                mUsersList.addAll(com.lockotron.mobi_o_tron.controller.Usuario.getAll(contexts[0]));
            } catch (IOException e) {
                serverErrorSnackbar.show();
                e.printStackTrace();
            } catch (ServerNotSetException e) {
                serverNotSetSnackbar.show();
                e.printStackTrace();
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void param) {
            synchronized (mUsersAdapter){
                mUsersAdapter.notifyDataSetChanged();
            }
        }
    }
}
