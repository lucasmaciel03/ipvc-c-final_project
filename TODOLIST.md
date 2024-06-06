# Lista de Tarefas para o Projeto de Programação 1

## Descrição do Projeto

Desenvolvimento de uma aplicação para a gestão de visitas de uma imobiliária.

## Objetivos

- A aplicação deve permitir gerir agentes imobiliários, clientes e propriedades.
- A imobiliária lida com diversas transações imobiliárias: compra, venda
  arrendamento de casas, apartamentos, escritórios, etc.
- A imobiliária tem espaço para 15 agentes.
- Sobre cada agente a aplicação deve armazenar: Nome, NIF, Morada, Contacto telefónico, Identificador na aplicação (sequencial) e data de nascimento.
- Neste contexto existem, pelo menos, 3 tipos de utilizadores: administrador, agente e cliente. (Possibilidade de Criação de Login)

## Tarefas

### Configuração Geral

- [x] Configurar o repositório do projeto.
- [x] Definir a estrutura de diretórios.
- [X] Configurar o controle de versão.
- Usar Ficheiros texto para armazenamento inicial de dados (Semana 1).

### Implementação de Login

- [x] Implementar a funcionalidade de login (Ficheiros binários - Semana 2).
- [ ] Implementar a funcionalidade de logout.
- [x] Implementar a funcionalidade de registo de utilizadores.

### Gestão de Propriedades

- [X] Implementar a funcionalidade para criar tipos de propriedades.
- [X] Implementar a funcionalidade para editar tipos de propriedades.
- [X] Implementar a funcionalidade para remover tipos de propriedades.
- [X] Implementar a funcionalidade para listar tipos de propriedades e seus preços.
    - Usar listas duplamente ligadas para gestão eficiente da lista de propriedades (Semana 9).

### Gestão de Agentes

- [x] Implementar a funcionalidade para criar agentes.
- [X] Implementar a funcionalidade para editar agentes.
- [X] Implementar a funcionalidade para remover agentes.
- [X] Implementer a funcionalidade para listar agentes por username.
- [X] Implementar a funcionalidade para listar agentes por ordem alfabética do nome (Algoritmos de ordenação - Semana 4).
- [X] Implementar a funcionalidade para listar agentes por idade ascendente (Algoritmos de ordenação - Semana 4).
- [X] Implementar a funcionalidade para colocar um agente como indisponível.
    - Armazenar dados dos agentes em estruturas de listas ligadas para fácil manipulação (Semana 7).

### Relatórios de Agentes

- [X] Desenvolver a funcionalidade para gerar um relatório em arquivo de texto com todas as informações dos agentes.

### Gestão de Clientes

- [X] Implementar a funcionalidade para criar clientes.
- [X] Implementar a funcionalidade para atualizar clientes.
- [X] Implementar a funcionalidade para remover clientes.
- [X] Implementar a funcionalidade para listar clientes por ordem alfabética do nome (Algoritmos de ordenação - Semana 4).
- [X] Implementar a funcionalidade para apresentar informações baseadas no NIF (Algoritmos de pesquisa - Semana 5).

### Agendamento e Gestão de Visitas

- [X] Implementar a funcionalidade para agendar uma visita (Listas duplamente ligadas - Semana 9).
- [X] Implementar a funcionalidade para listar todas as visitas de hoje e de um determinado dia, ordenadas por hora.
- [X] Implementar a funcionalidade para listar visitas de um determinado cliente.
- [X] Implementar a funcionalidade para listar visitas por tipo de propriedade.
- [X] Implementar a funcionalidade para saber o histórico de visitas a uma determinada propriedade.
- [X] Implementar a funcionalidade para simular uma visita (incluir agente, data e hora).

### Relatórios de Visitas

- [X] Implementar a funcionalidade para listar as visitas em que o cliente não compareceu em um determinado dia.
- [X] Implementar a funcionalidade para saber quanto foi faturado hoje e este mês por cada tipo de propriedade.
- [X] Implementar a funcionalidade para saber quantas visitas cada agente realizou este mês.
- [X] Implementar a funcionalidade para gerar relatórios financeiros diários e mensais por tipo de propriedade.

### Gestão de Filas de Espera

- [ ] Implementar a funcionalidade para adicionar um cliente à fila de espera para visitas com duração estimada da visita.
- [ ] Implementar a funcionalidade para remover o próximo cliente da fila de espera quando for atendido.
- [ ] Implementar a funcionalidade para listar todos os clientes na fila de espera e a respectiva duração estimada da visita.
- [ ] Implementar a funcionalidade para apresentar o próximo cliente a ser atendido.
- [ ] Implementar a funcionalidade para calcular o tempo de espera estimado para todos os elementos da fila (Árvores - Semana 11, opcional).

### Testes

- [ ] Desenvolver testes unitários para a gestão de propriedades.
- [ ] Desenvolver testes unitários para a gestão de agentes.
- [ ] Desenvolver testes unitários para a gestão de clientes.
- [ ] Desenvolver testes unitários para o agendamento e gestão de visitas.
- [ ] Testar a funcionalidade geral do sistema.

### Documentação

- [ ] Documentar o código fonte.
- [ ] Preparar manual do usuário.
- [ ] Preparar relatório do projeto.
- [ ] Atualizar o arquivo README com o status final do projeto.

### Passos Finais

- [ ] Revisar todas as funcionalidades.
- [ ] Depurar quaisquer problemas.
- [ ] Teste final do sistema com os membros do grupo.
- [ ] Preparar o projeto para a submissão.

## Notas

- Manter o código limpo e organizado.
- Manter o ficheiro TODOLIST.md atualizado.
