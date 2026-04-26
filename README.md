# Elevador Inteligente Acessível (EIA)

## 📌 Descrição

O projeto Elevador Inteligente Acessível (EIA) tem como objetivo melhorar a acessibilidade em elevadores dentro do Senac, promovendo autonomia para pessoas com deficiência (PCDs) por meio de uma solução baseada em IoT integrada com aplicação mobile.

---

## 🎯 Problema

Os elevadores atuais não possuem mecanismos adaptativos, resultando em:

- Dependência de terceiros
- Tempo insuficiente de abertura das portas
- Risco de acidentes
- Baixa autonomia para usuários com mobilidade reduzida

---

## 💡 Solução

Desenvolvimento de um sistema IoT que permite ativar automaticamente o modo acessível do elevador.

Funcionalidades principais:

- Ativação por botão físico
- Aumento do tempo de abertura da porta
- Registro de eventos
- Integração com aplicação mobile

---

## 🏗️ Arquitetura

Fluxo do sistema:

Botão → ESP32 → Wi-Fi → MQTT → Backend → App Mobile

---

## ⚙️ Tecnologias Utilizadas

- ESP32
- MQTT (broker público)
- Wi-Fi
- Firebase (backend)
- Flutter / Figma (mobile)
- GitHub (versionamento)

---

## 🔄 Funcionamento

1. Usuário pressiona o botão
2. ESP32 detecta o evento
3. Sistema ativa o modo acessível
4. LED simula a porta aberta por mais tempo
5. Evento é enviado via MQTT
6. Dados podem ser visualizados no app

---

## 📋 Requisitos

### Funcionais
- Ativar modo acessível
- Ajustar tempo da porta
- Registrar eventos

### Não Funcionais
- Resposta em até 2 segundos
- Comunicação estável
- Confiabilidade
- Segurança básica

---

## 🔐 Segurança

- Validação de comandos
- Controle básico de acesso
- Registro de logs

---

## 🧪 Protótipo

### IoT
- ESP32 conectado ao Wi-Fi
- Botão físico
- LED simulando porta
- Comunicação MQTT

### Mobile
- Protótipo de interface com:
  - Tela de status
  - Histórico de eventos

---

## 📊 Backlog

Gerenciado via GitHub Projects (Kanban)

Exemplos:

- Como usuário, quero ativar o modo acessível
- Como sistema, quero registrar eventos
- Como admin, quero visualizar logs

---

## 🚀 Como Executar

### IoT

1. Conectar ESP32
2. Abrir código em /iot
3. Configurar Wi-Fi
4. Fazer upload
5. Monitorar via Serial Monitor

---

## 📁 Estrutura do Projeto

/iot → código do ESP32
/mobile → protótipo ou app
/docs → documentação
/assets → imagens
