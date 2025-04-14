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

def main():
    lista_arquivos = ["header.h", "jogador.cpp", "jogador.h", "jogo.cpp", "jogo.h", "professor.cpp", "professor.h", "util.cpp", "util.h", "gamificacao.ino"]
    lista_palavras_proibidas = ["#endif","HEADER_H", "JOGADOR_H", "JOGO_H", "PROFESSOR_H", "UTIL_H"]

    lista_includes, lista_codigo = extrair_codigo(lista_arquivos)
    includes_filtrados = filtrar_codigo(lista_includes, lista_arquivos)
    codigo_filtrado = filtrar_codigo(lista_codigo, lista_palavras_proibidas)

    for include in includes_filtrados:
        print(include)

    for codigo in codigo_filtrado:
        print(codigo)
    


if __name__ == "__main__":
    main()
