# Projeto de Extensão — Sistema Gamificado de Ensino com Arduino

Projeto de extensão da **Universidade de Brasília (UnB)**, coordenado pelo **Prof. Dr. Rafael Shayani**, do **Departamento de Engenharia Elétrica**.

Este projeto tem como objetivo a implementação de um sistema **gamificado de ensino** em escolas públicas do **Distrito Federal**, utilizando placas **Arduino** como ferramenta de apoio pedagógico.

---

## 🧠 Objetivo

Criar uma dinâmica de **quizzes interativos** com foco em engajar estudantes do ensino básico por meio da tecnologia, promovendo a aprendizagem ativa e divertida.

---

## 🛠️ Tecnologias Utilizadas

- **Arduino IDE**
- **Linguagem C++**
- **Simulações com Tinkercad**  
  🔗 Link para a simulação: `https://www.tinkercad.com/things/771Upd9yJbP-area-of-test?sharecode=csdleqh-ssqdYM-BmTQKned35VJi-PZKUBT2ELMBJ84`
- **Comunicação I2C** para conexão entre dispositivos
- **Expansores de I/O PCF8574** para permitir múltiplos dispositivos conectados ao barramento

---

## 🧩 Estrutura do Sistema

- O sistema é composto por **7 dispositivos Arduino**:
  - **6 dispositivos de alunos**, responsáveis por responder aos quizzes
  - **1 dispositivo mestre (professor)**, que coordena a dinâmica e define a resposta correta de cada pergunta
- Todos os dispositivos se comunicam via **protocolo I2C**, onde o **professor atua como mestre**, e os **alunos como escravos**
- O **PCF8574** permite a expansão das entradas e saídas digitais, viabilizando o uso de botões e LEDs nos módulos dos alunos

---

## 📌 Funcionalidades

- O professor pode **definir a resposta correta** via botão físico
- Cada aluno responde aos quizzes por meio de um botão específico (A, B, C, D)
- O sistema valida automaticamente quem acertou ou errou
- Possibilidade futura de exibir pontuações em um display LCD

---

## 🤝 Impacto Social

Este projeto visa fomentar o interesse por **tecnologia e engenharia** em jovens da rede pública de ensino, utilizando uma abordagem prática, acessível e lúdica.

---

## 💬 Contato

Coordenador: **Prof. Dr. Rafael Shayani**  
Departamento de Engenharia Elétrica - UnB  
Projeto desenvolvido por estudantes de Engenharia da Computação,  Engenharia Mecatrônica e Engenharia Florestal.

---

