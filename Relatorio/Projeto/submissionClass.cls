% submissionClass.cls
%  Submission Model class
%  Intel® Embedded Systems Competition 2016
%  VI Brazilian Symposium on Computing Systems Engineering (SBESC)
% 2016-Apr-01 Paula submissaocompeticaointel (at) gmail.com
% Changelog:
%
% 2016-04-01 v1.00: Initial release
%

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{submissionClass}[2016/03/31 submission model class]
\LoadClass{article}

\RequirePackage[latin1]{inputenc}
\RequirePackage{extsizes}
\RequirePackage{titlesec}
\RequirePackage{ragged2e}

%New Commands and Variables used in the class
% \def\@projectname{Project name}
% \newcommand{\setprojectname}[1]{\def\@projectname{#1}}
% \newcommand{\show@projectname}{\@projectname}
% \newcommand{\projectname}{\show@projectname}

\newcommand{\equipe}[3]{
    #1 {\large\textperiodcentered}  \hfill #2 {\large\textperiodcentered}  \raggedleft #3 \\
}

\newcommand{\idEquipe}[2]{ 
    \newline #1 {\raggedright} 	
	\justify #2 {\normalfont}  \\
}

\newcommand{\paragrafo}[1]{
	\justify #1 
}

% Page layout
\RequirePackage[left=3.17cm,right=3.17cm,top=2.54cm,bottom=2.54cm]{geometry}

% Packages necessary to add fluff to header/footer
\RequirePackage{graphicx}
\RequirePackage{fancyhdr}

\fancypagestyle{submissionClass}{%
	\fancyhf{} % clear all six fields
	\renewcommand{\headrulewidth}{0.4pt}
	\renewcommand{\footrulewidth}{0pt}
	\fancyhead[R]{%
		\raisebox{2pt}
		{\includegraphics[keepaspectratio,height=0.78cm]{intel_icon.png}}
	}
	
	\fancyhead[L]{%
		\includegraphics[keepaspectratio,height=0.98cm]{sbesc_icon.png}
	}
		\fancyhead[C]{%
		\raisebox{4pt}{%
			\parbox[b][2em][c]{0.5\textwidth\inputencoding{latin1}}{%
				\centering Project Submission
			}
		}
	}
	\fancyfoot[C]{\thepage}
}
\pagestyle{submissionClass}
\setlength{\headheight}{32pt}

\titleformat{\section}         % Customise the \section command 
  {\Large\scshape\raggedright} % Make the \section headers large (\Large),
                               % small capitals (\scshape) and left aligned (\raggedright)
  {}{0em}                      % Can be used to give a prefix to all sections, like 'Section ...'
  {}                           % Can be used to insert code before the heading
  [\titlerule]                 % Inserts a horizontal line after the heading
	
\titleformat{\subsection}
  {\large\scshape\raggedright} 
  {}{0em}
  {}
  [\titlerule] 

  

\newcommand{\sectionbreak}{\clearpage}
