# TP (Parte I)_Laís Schmitz_Raquel Nascimento

Este projeto implementa um sistema básico de cadastro e consulta de pacientes. Nele, é possível realizar a consulta por nome ou CPF, imprimir a lista dos pacientes (20 registros por página) e acessar o menu para outras operações. Algumas funções de atualização, remoção e inserção de pacientes estão presentes como _stubs_ (a serem na próxima parte do trabalho).

---

## Estrutura do Repositório

```
├── bd_paciente.csv # Base de dados no formato CSV
├── main.c # Código-fonte principal que contém a função main e a lógica do menu.
└── arquivo.h # Declarações das funções utilizadas
```

---

### Sobre os arquivos:

---

- **bd_paciente.csv**: Arquivo de dados que deve estar no mesmo diretório. Ele deve conter os registros dos pacientes seguindo o formato: `id,cpf,nome,idade,data_cadastro`

---

- **main.c**: Contém todas as implementações do fluxo do programa, incluindo a leitura dos dados do CSV, execução do menu principal, funções de consulta, impressão da lista e os _stubs_ para futuras implementações de inserção, remoção e atualização do paciente.

---

- **arquivo.h**: Declarações das funções que compõem o sistema (menu, consulta, atualização, remoção, inserção, impressão e verificação se o arquivo CSV está vazio).

---

## TAD utilizado:

O projeto utiliza o TAD **Paciente**, definido como uma `struct` em `main.c`, que possui os seguintes campos:

- `id` (int): Número identificador do paciente.
- `cpf` (char[20]): CPF do paciente.
- `nome` (char[100]): Nome completo do paciente.
- `idade` (int): Idade do paciente.
- `data_cadastro` (char[15]): Data de cadastro do paciente.

Este TAD é a base para manipulação dos dados, permitindo que as operações de consulta e impressão sejam realizadas de forma consistente e organizada (além de ser essencial para a proxima parte do trabalho).

---

## Instruções para Execução

1. **Pré-requisitos**:  
 - Um compilador de C.  
 - Certifique-se de ter o arquivo `bd_paciente.csv` no mesmo diretório do código.  
 
---

2. **Compilação**:  
 Abra o terminal na pasta do projeto e execute o comando abaixo:

```
gcc main.c -o cadastro_pacientes
```

---

3. **Execução**:  
Após a compilação, execute o programa com:

```
./cadastro_pacientes
```

O menu apresentado permitirá a escolha entre consultar pacientes, atualizar, remover, inserir ou imprimir a lista.  

---

## Principais Decisões de Implementação

- **TAD Paciente**:  
O sistema utiliza o TAD *Paciente* para encapsular os dados de cada paciente. Essa escolha possibilita uma manipulação clara e objetiva das informações e facilita futuras expansões do projeto.

---

- **Consulta e Impressão**:  
A consulta pode ser realizada tanto por nome quanto por CPF, utilizando funções auxiliares para busca sem diferenciar letras maiúsculas e minúsculas. Além disso, a lista de pacientes é apresentada com 20 registros por página, oferecendo ao usuário a opção de continuar a visualizar ou retornar ao menu inicial.

---

- **Funções Stub**:  
As funções para atualizar, remover e inserir pacientes são definidas como _stubs_. Essa estratégia permite uma futura implementação sem quebrar o fluxo principal do sistema, além de facilitar a visualização do que será a versão final do sistema.

---

- **Validação do Arquivo CSV**:  
Antes de realizar as operações, o sistema verifica se o arquivo CSV possui conteúdo para evitar erros em casos de arquivo vazio.

---

## Sobre o Código

- **Rotinas de Busca**:  
Foi desenvolvida uma função auxiliar (`strcasestr_custom`) para buscar substrings de forma case insensitive, garantindo que a busca por nomes seja feita sem restrição quanto à capitalização.

---

- **Interface com o Usuário**:  
O menu principal e os controles de navegação (especialmente na função de impressão com paginação) foram desenvolvidos para serem intuitivos, proporcionando uma melhor experiência ao usuário e buscando otimizar a execução do programa.

---

Este README.md oferece uma visão completa do sistema, desde a estrutura dos arquivos até as principais decisões tomadas e futuras melhorias.

