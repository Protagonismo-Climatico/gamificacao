def extrair_codigo(lista_arquivos):
    lista_includes = []
    codigo = []
    for arquivo in lista_arquivos:
        with open(arquivo, 'r') as entidade:
            for linha in entidade:
                if('#include' in linha):
                    lista_includes.append(linha)
                else:
                    codigo.append(linha)

    return lista_includes, codigo

def filtrar_codigo(lista_codigo,lista_filto):
    flag = 0
    lista_filtrada = []
    for include in lista_codigo:
        for arquivo in lista_filto:
            if arquivo in include:
                flag = 1
                break
        if flag == 0:
            lista_filtrada.append(include)
        flag = 0
    return lista_filtrada

def escrever_arquivo(includes_filtrados, codigo_filtrado):
    with open('codigo.txt', 'w') as arquivo:
        for include in includes_filtrados:
            arquivo.write(include)
        for codigo in codigo_filtrado:
            arquivo.write(codigo)
    print("Arquivo gerado, more. <3")

def main():
    lista_arquivos = ["header.h","util.h", "jogador.h","professor.h", "jogo.h", "jogador.cpp", "jogo.cpp", "professor.cpp", "util.cpp", "gamificacao.ino"]
    lista_palavras_proibidas = ["#endif","HEADER_H", "JOGADOR_H", "JOGO_H", "PROFESSOR_H", "UTIL_H"]

    lista_includes, lista_codigo = extrair_codigo(lista_arquivos)
    includes_filtrados = filtrar_codigo(lista_includes, lista_arquivos)
    codigo_filtrado = filtrar_codigo(lista_codigo, lista_palavras_proibidas)

    escrever_arquivo(includes_filtrados, codigo_filtrado)
    


if __name__ == "__main__":
    main()
