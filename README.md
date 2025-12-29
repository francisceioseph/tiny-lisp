# Tiny-Lisp

Um interpretador Lisp minimalista e elegante escrito em C, focado em segurança de memória através do ecossistema **Fil-C**.

## 🚀 Sobre o Projeto

O Tiny-Lisp é um interpretador de dialeto Lisp desenvolvido para ser simples, didático e robusto. O grande diferencial deste projeto é a utilização do **Fil-C**, um compilador que garante segurança de memória (memory safety) para código C, prevenindo vulnerabilidades comuns como buffer overflows e dangling pointers.

### ✨ Funcionalidades

* **REPL Avançado**: Interface interativa utilizando `libreadline` com suporte a histórico e edição de linha.
* **Aritmética Flexível**: Operações variádicas como `(+ 1 2 3 4)`.
* **Lógica e Condicionais**: Suporte a `cond`, `not`, e comparadores (`=`, `<`, `>`, etc.).
* **Manipulação de Listas**: Primitivas clássicas como `car`, `cdr`, `cons` e `list`.
* **Recursão**: Capacidade de definir funções complexas como a sequência de Fibonacci.
* **Modo Script**: Execute arquivos `.lisp` diretamente pelo terminal.

## 📂 Estrutura do Repositório

* **include/**: Protótipos e definições de tipos (.h).
* **src/**: Implementação da lógica do interpretador (.c).
* **examples/**: Exemplos de código Lisp.
* **Makefile**: Automação de compilação configurada para Fil-C.
* **compile_flags.txt**: Configurações para LSP (clangd).

## 🛠️ Como Compilar e Rodar

### Pré-requisitos

1. **Fil-C**: Certifique-se de que o compilador `filc` está instalado.
2. **Readline**: Instale a biblioteca de desenvolvimento:
`sudo apt-get install libreadline-dev`

### Compilação

Execute `make` na raiz do projeto.

### Execução

Para o modo interativo (REPL): `./tiny-lisp`
Para executar um arquivo: `./tiny-lisp examples/fibonacci.lisp`

## 📜 Exemplo de Código

```lisp
(define fib (lambda (n) 
  (cond ((= n 0) 0) 
        ((= n 1) 1) 
        (t (+ (fib (- n 1)) (fib (- n 2)))))))

(print (fib 10)) ; Resultado: 55

```

## 🛡️ Segurança com Fil-C

Este projeto foi compilado utilizando o **Fil-C**, garantindo que todas as manipulações de ponteiros sejam verificadas em tempo de execução, tornando o interpretador imune a bugs de corrupção de memória.

---

Desenvolvido por [Francis Souza](https://github.com/francisceioseph)
