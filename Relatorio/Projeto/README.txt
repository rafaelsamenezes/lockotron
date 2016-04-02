Submission Model - Latex - v1.0.0
----------------------------------
Testado no ambiente TeXworks (MiKTeX 2.9)

Texto codificado com ISO 8859-1 (latin1). Dependendo do programa usado para abrir o arquivo é necessário mudar o Encoding default UFT-8 para ISO 8859-1 e atualizar a página.

Todas as modificações são realizadas no arquivo *.tex
----------------------------------
How-to-edit

* 'Dados da Proposta'.
Modificar apenas o necessário de cada campo, por exemplo:
\textbf{Nome do Projeto:} Título projeto\\ -- Apenas substituir o trecho 'Título projeto', deixando a marcação inicial e a dupla barra invertida final (\\).

* 'Identificação e histórico da equipe'
Item \paragrafo... pode ser removido

Para cada membro da equipe (aluno e orientador) usar o comando \idEquipe para cada um, respeitando a ordem e conteúdo dos argumentos.
\idEquipe{Nome}{Descrição.}  -- Editar campos 'Nome' e 'Descrição', mantendo as chaves

* 'Descrição do sistema' e 'Justificativa'
Item \paragrafo... pode ser removido

Acrescentar cada novo parágrafo usando o comando \paragrafo{texto}

* 'Cronograma'
Não retirar as barras invertidas ao final de cada item do cronograma