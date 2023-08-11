#esse script gera o texto do overleaf para a criacao de um pdf do Notebook
import os


contextos = ["section", "subsection", "subsubsection", "paragraph"]
#comando com a o contexto, pode ser algo como section ou subsection,
#server para o indice
def comando_latex_secao(contexto, texto):
    print("\\" + contexto + "{" + texto + "}")
    print()

#comando que faz adicionar o codigo mediante o arquivo no overleaf
def comando_adiciona_codigo(nome, file):
    print("\lstinputlisting[language=C++]{" + file +"}")
    print()

#comando de quebra de linha
def comando_quebra_pagina():
    print("\clearpage")
    print()


def main():

    #imprimindo inicio do documento overleaf
    with open("inicio_overleaf.txt", 'r', encoding='utf-8') as infile:
        for line in infile:
            print(line, end = '')

    #vasculha a partir do contexto desse arquivo, para fazer com
    #que o arquivo nao fique na raiz do repositorio, mude "."
    for subdir, dirs, files in os.walk("."):
        #ignorara a past .git
        if(subdir[0:6] == "./.git"):
            continue
        topicos = subdir.split("/")[1:]
        id_contexto = len(topicos)-1
        #significa que esta na pasta base do repositorio
        if(id_contexto == -1):
            continue
        #ignorar isto
        if(topicos[-1] == "scripts"):
            continue
        comando_latex_secao(contextos[id_contexto], topicos[-1])

        for file in files:
            nome = file.split(".")[0]
            extensao = file.split(".")[-1]
            if(extensao != "cpp"):
                continue
            comando_latex_secao(contextos[id_contexto+1], nome)
            comando_adiciona_codigo(nome, file)
    
    #imprimindo final do documento overleaf
    print("\end{" + "document}")

if __name__ == "__main__":
    main()