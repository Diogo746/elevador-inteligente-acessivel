# 🚀 Elevador Inteligente Acessível (EIA)

## 📌 Descrição

O projeto **Elevador Inteligente Acessível (EIA)** tem como objetivo melhorar a acessibilidade em elevadores no ambiente do Senac, promovendo maior autonomia para pessoas com deficiência (PCDs) por meio de uma solução baseada em **IoT integrada com aplicação mobile e backend em nuvem**.

---

## 🎯 Problema

Os elevadores convencionais não possuem mecanismos adaptativos inteligentes, resultando em:

- Dependência de terceiros para uso do elevador  
- Tempo insuficiente de abertura de portas  
- Risco de incidentes durante a entrada  
- Baixa autonomia para usuários com mobilidade reduzida  

---

## 💡 Solução

O sistema proposto implementa um **modo acessível inteligente**, ativado por hardware, capaz de adaptar o comportamento do elevador.

Principais funcionalidades:

- Ativação do modo acessível via botão físico ou sensor  
- Ajuste automático do tempo de abertura da porta  
- Comunicação em tempo real entre dispositivos  
- Registro de eventos no backend  
- Visualização de status via aplicação mobile  

---

### 📌 Diagrama de Caso de Uso

![Caso de Uso](assets/CasodeUso.png)

---

## 🏗️ Arquitetura do Sistema

O sistema segue uma arquitetura distribuída baseada em IoT:
Botão / Sensor → ESP32 → Wi-Fi → MQTT → Backend (Firebase) → Aplicação Mobile


### 📷 Diagrama de Arquitetura

![Diagrama de Arquitetura](assets/Diagrama.png)

---

## ⚙️ Tecnologias Utilizadas

- ESP32 (microcontrolador)
- MQTT (comunicação IoT)
- Wi-Fi
- Firebase (backend e armazenamento)
- Flutter / Figma (interface mobile)
- Git/GitHub (controle de versão)

---

## 🔄 Funcionamento

1. Usuário ativa o sistema por botão ou sensor  
2. O ESP32 detecta o evento  
3. O modo acessível é ativado automaticamente  
4. O tempo de abertura da porta é ajustado  
5. O evento é enviado via MQTT para o backend  
6. Os dados são armazenados no Firebase  
7. O status pode ser visualizado no aplicativo mobile  

---

### 🔁 Fluxograma do Sistema

![Fluxograma](assets/Fluxograma.png)
---

### 🛡️ Arquitetura Resiliente / Edge Computing

![Fluxograma Resiliente](assets/ArquiteturaResiliente.png)

---

### 🔄 Diagrama de Sequência

![Diagrama de Sequência](assets/DiagramaDeSequencia.png)

---

## 📋 Requisitos

### ✔️ Funcionais

- Ativação do modo acessível  
- Ajuste automático do tempo da porta  
- Comunicação entre ESP32 e backend via MQTT  
- Registro de eventos no Firebase  
- Exibição do estado do elevador no sistema  
- Processamento de sensores físicos  
- Retorno automático ao estado padrão  

### ✔️ Não Funcionais

- Tempo de resposta inferior a 2 segundos  
- Comunicação MQTT confiável (QoS 1)  
- Sistema com alta estabilidade de conexão  
- Baixo consumo de recursos no ESP32  
- Interface simples e intuitiva  
- Não armazenamento de dados pessoais sensíveis (LGPD)  

---

## 🔐 Segurança e LGPD

O sistema segue o princípio de **Security by Design**, com foco em segurança desde a concepção.

- Validação de comandos no backend  
- Controle de acesso a dispositivos autorizados  
- Comunicação segura entre IoT e backend  
- Registro de logs para auditoria  
- Coleta mínima de dados operacionais  
- Conformidade com a LGPD (sem dados pessoais identificáveis)  

---

## 🧪 Protótipo

### 📡 IoT
- ESP32 conectado via Wi-Fi  
- Botão físico ou sensor de entrada  
- LED simulando comportamento da porta  
- Comunicação via MQTT


### 📱 Mobile
- Interface de monitoramento  
- Visualização de status do elevador  
- Histórico de eventos  

---

## 📊 Backlog

O projeto é organizado em tarefas no formato Kanban (GitHub Projects), dividido em:

- Funcionalidades essenciais (MVP)  
- Funcionalidades de suporte  
- Melhorias futuras  

---

## 🚀 Como Executar

### 📡 IoT (ESP32)

1. Conectar o ESP32 ao computador  
2. Abrir o projeto na IDE Arduino  
3. Configurar credenciais de Wi-Fi  
4. Fazer upload do código  
5. Monitorar via Serial Monitor  

---

## 📁 Estrutura do Projeto

/iot → Código do ESP32
/mobile → Aplicação mobile
/docs → Documentação técnica
/assets → Imagens e diagramas


---

## 📌 Observação Final

Este projeto integra conceitos de **IoT, redes e desenvolvimento mobile**, demonstrando uma solução funcional para acessibilidade inteligente em ambientes institucionais.

---

ReadMe 2

# 🚀 Elevador Inteligente Acessível (EIA)

## 📌 Descrição

O projeto **Elevador Inteligente Acessível (EIA)** tem como objetivo promover maior autonomia para pessoas com mobilidade reduzida por meio de uma solução baseada em **Internet das Coisas (IoT)**.

O sistema utiliza um dispositivo ESP32 conectado à rede Wi-Fi para registrar solicitações de acessibilidade, processar eventos localmente e enviá-los para uma API REST responsável pelo armazenamento das informações em banco de dados MySQL.

---

## 🎯 Problema

Elevadores convencionais frequentemente não oferecem mecanismos inteligentes que auxiliem pessoas com deficiência ou mobilidade reduzida, resultando em:

- Dependência de terceiros para utilização do elevador;
- Tempo insuficiente para entrada e saída;
- Falta de monitoramento dos eventos de acessibilidade;
- Baixa autonomia dos usuários;
- Ausência de métricas para análise e melhoria do serviço.

---

## 💡 Solução

O EIA implementa um sistema inteligente capaz de registrar solicitações de acessibilidade e disponibilizar essas informações para monitoramento.

Principais funcionalidades:

- Acionamento por botão físico;
- Registro de eventos em tempo real;
- Sincronização automática de data e hora via NTP;
- Comunicação com API REST através de HTTP POST;
- Armazenamento em banco MySQL;
- Feedback visual por LED;
- Exibição de mensagens operacionais em display LCD I2C;
- Reconexão automática em caso de falhas de rede.

---

## 📌 Diagrama de Caso de Uso

![Caso de Uso](assets/CasodeUso.png)

---

## 🏗️ Arquitetura do Sistema

A solução segue uma arquitetura distribuída baseada em IoT.

```text
Usuário
   ↓
Botão de Acessibilidade
   ↓
ESP32
   ↓
Wi-Fi
   ↓
API REST
   ↓
Banco MySQL
   ↓
Aplicação Web/Mobile
```

### 📷 Diagrama de Arquitetura

![Diagrama de Arquitetura](assets/Diagrama.png)

---

## ⚙️ Tecnologias Utilizadas

### Hardware

- ESP32
- Botão físico
- LED indicador
- Display LCD I2C

### Software

- Arduino IDE
- Linguagem C++
- ArduinoJson
- HTTPClient
- Wi-Fi Library
- NTP

### Backend

- API REST
- MySQL

### Ferramentas

- Git
- GitHub
- Vercel
- V0

---

## 🔄 Funcionamento

1. O usuário aciona o botão de acessibilidade;
2. O ESP32 detecta o evento;
3. O sistema sincroniza data e hora;
4. Um payload JSON é criado;
5. O evento é enviado para a API REST;
6. Os dados são armazenados no MySQL;
7. O LCD exibe o resultado da operação;
8. O LED confirma visualmente o processamento do evento.

---

### 🔁 Fluxograma do Sistema

![Fluxograma](assets/Fluxograma.png)

---

### 🛡️ Arquitetura Resiliente / Edge Computing

![Fluxograma Resiliente](assets/ArquiteturaResiliente.png)

---

### 🔄 Diagrama de Sequência

![Diagrama de Sequência](assets/DiagramaDeSequencia.png)

---

## 📋 Requisitos

### ✔️ Funcionais

- Detectar acionamento do botão;
- Registrar eventos de acessibilidade;
- Sincronizar data e hora via NTP;
- Gerar payload JSON;
- Enviar informações para API REST;
- Armazenar dados em banco MySQL;
- Exibir mensagens em LCD;
- Acionar LED de confirmação.

### ✔️ Não Funcionais

- Tempo de resposta inferior a 2 segundos;
- Reconexão automática da rede Wi-Fi;
- Tratamento de falhas HTTP;
- Baixo consumo de recursos do ESP32;
- Escalabilidade para aplicações futuras;
- Conformidade com LGPD.

---

## 🔐 Segurança e LGPD

O projeto adota princípios de **Security by Design**.

Medidas implementadas:

- Registro apenas de dados operacionais;
- Ausência de informações pessoais dos usuários;
- Identificação do dispositivo por MAC Address;
- Comunicação estruturada via API REST;
- Preparação para uso de credenciais protegidas;
- Conformidade com os princípios da LGPD.

---

## 🧪 Protótipo

### 📡 IoT

- ESP32 conectado à rede Wi-Fi;
- Botão físico para acionamento;
- Display LCD I2C para feedback operacional;
- LED indicador de confirmação;
- Comunicação com API REST via HTTP.

### 🗄️ Backend

- API REST para recebimento dos eventos;
- Persistência dos dados em banco MySQL;
- Registro de data, hora e dispositivo responsável.

### 📱 Aplicação Web/Mobile

- Dashboard de monitoramento;
- Consulta de eventos registrados;
- Visualização de estatísticas;
- Histórico de acionamentos.

---

## 📸 Evidências do Projeto

### Protótipo Físico

*(Inserir foto do ESP32 montado com botão, LED e LCD)*

### Serial Monitor

*(Inserir captura de tela da execução do firmware)*

### Aplicação Web/Mobile

*(Inserir capturas de tela da interface desenvolvida no V0)*

---

## 📊 Backlog

O projeto é organizado utilizando GitHub Projects no modelo Kanban.

Divisão das atividades:

- MVP (Produto Mínimo Viável);
- Melhorias funcionais;
- Evoluções futuras;
- Integrações complementares.

---

## 🚀 Como Executar

### ESP32

1. Conectar o ESP32 ao computador;
2. Abrir o projeto na Arduino IDE;
3. Configurar credenciais Wi-Fi;
4. Configurar URL da API;
5. Realizar upload do firmware;
6. Monitorar execução pelo Serial Monitor.

---

## 📁 Estrutura do Projeto

```text
/iot
  └── Código ESP32

/backend
  └── API REST

/database
  └── Scripts MySQL

/mobile
  └── Aplicação Web/Mobile

/docs
  └── Documentação

/assets
  └── Diagramas e imagens
```

---

## 🔮 Melhorias Futuras

- Integração com sensores de presença;
- Dashboard analítico avançado;
- Notificações em tempo real;
- Aplicativo mobile completo;
- Monitoramento de múltiplos elevadores;
- Indicadores de acessibilidade e uso.

---

## 📌 Conclusão

O Elevador Inteligente Acessível (EIA) demonstra a aplicação prática de conceitos de Internet das Coisas, sistemas embarcados, comunicação em rede e acessibilidade.

A solução integra hardware, software e banco de dados para criar uma plataforma capaz de registrar eventos de acessibilidade, promover monitoramento operacional e servir como base para futuras evoluções voltadas à inclusão e transformação digital.
