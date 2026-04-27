# 5. REQUISITOS DO SISTEMA

## 5.1 Requisitos Funcionais

| ID   | Requisito | Descrição / Critério de Aceite |
|------|----------|---------------------------------|
| RF01 | Ativação de Acessibilidade | O sistema deve permitir a ativação do "Modo Acessível" através de botões físicos adaptados ou sensores de presença/proximidade. |
| RF02 | Ajuste de Tempo de Porta | Ao ser ativado o Modo Acessível, o sistema deve estender o tempo de abertura da porta de acordo com os parâmetros de acessibilidade configurados. |
| RF03 | Comunicação em Tempo Real | O ESP32 deve trocar mensagens com o backend via protocolo MQTT, garantindo que o estado do hardware seja refletido no sistema. |
| RF04 | Registro de Atividades | Todo evento (ativação, abertura, fechamento) deve ser persistido no Firebase com a data e hora exatas (timestamp). |
| RF05 | Dashboard de Monitoramento | A interface do usuário deve exibir, em tempo real, se o elevador está em uso, em modo padrão ou em modo acessível. |
| RF06 | Comando Remoto | O backend deve ser capaz de enviar sinais ao ESP32 para realizar testes ou resetar o estado do hardware à distância. |
| RF07 | Processamento de Sinais | O sistema deve tratar os sinais analógicos/digitais dos sensores físicos, filtrando ruídos para evitar ativações falsas. |
| RF08 | Auditoria de Logs | Deve ser possível extrair um relatório dos eventos armazenados para análise de fluxo e uso da acessibilidade. |
| RF09 | Restabelecimento Padrão | Após a conclusão do ciclo de uso (porta fechada por tempo X), o sistema deve desativar o modo acessível automaticamente. |

---

## 5.2 Requisitos Não Funcionais

| ID   | Requisito | Categoria | Descrição |
|------|----------|-----------|-----------|
| RNF01 | Baixa Latência | Desempenho | O tempo entre o acionamento do sensor e a resposta do sistema não deve exceder 2 segundos. |
| RNF02 | Segurança de Acesso | Segurança | Apenas o backend autorizado e o hardware autenticado podem publicar mensagens nos tópicos MQTT do projeto. |
| RNF03 | Confiabilidade MQTT | Confiabilidade | Deve-se utilizar QoS 1 para garantir que a mensagem de ativação seja entregue ao menos uma vez ao broker. |
| RNF04 | Robustez do Protótipo | Disponibilidade | O sistema deve ser capaz de se reconectar automaticamente ao Wi-Fi e ao broker em caso de queda de sinal. |
| RNF05 | Escalabilidade de Hardware | Manutenibilidade | O firmware deve ser modular, permitindo a adição de novos sensores (ex: ultrassônico) sem alterar a lógica central. |
| RNF06 | Usabilidade (UX) | Usabilidade | A interface de monitoramento deve ser intuitiva, utilizando cores e ícones universais para indicar o estado do elevador. |
| RNF07 | Eficiência de Recursos | Desempenho | O código no ESP32 deve priorizar o uso eficiente de memória e ciclos de CPU para evitar travamentos. |
| RNF08 | Privacidade (LGPD) | Conformidade | O sistema não coletará dados que identifiquem o usuário (como fotos ou nomes), apenas o fato da ativação. |
