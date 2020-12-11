# Projeto - Simulação Epidemiológica

### **DISCENTES**:
- GILDO CORDEIRO DUARTE
- JEFFERSON FELIPE DA SILVA

### **DESCRIÇÃO DO PROJETO**

Modelos epidemiológicos computacionais (MEC) são utilizados para a compreensão da dinâmica de uma epidemia ou afim, e são, portanto, ferramentas essenciais na determinação de políticas públicas para combate e prevenção de doenças. A transmissão de uma doença infecciosa pode ocorrer por diversas formas, como contato direto entre indivíduos, por via aérea, por contato com superfícies contaminadas, via vetor de transmissão, dentre outros.

Nesse modelo, um indivíduo da população S pode permanecer em S ou ir para a população I, caso seja infectado. Um indivíduo de I pode, então, se recuperar ou falecer. Indivíduos que pertençam a R não mudam de população. A interação entre essas populações pode ser descrita pelas equações abaixo:

- *S(t)=S(t-1)-h.b.S(t-1).I(t-1)*
- *I(t)=I(t-1)+h.[b.S(t-1).I(t-1)-k.I(t-1)]*
- *R(t)=R(t-1)+h.k.I(t-1)*
- *tempo(t)=tempo(t-1)+h*

`OBS.: O vetor tempo é utilizado para incrementar para armazenar o valor do tempo a cada iteração do laço de repetição`

Implemente o modelo SIR, isto é, encontre os valores de S(t), I(t) e R(t) ao longo de um determinado período de simulação. A partir do cenário definido pelos parâmetros de entrada do simulador (Cenário 0), rode também dois outros cenário com diferentes estratégias de contenção:

Cenário 1: Distanciamento/uso de máscaras
Esta estratégia refere-se à facilidade/dificuldade de contágio na população, influenciando assim a variável b da equação. Para este cenário, suponha que o tempo de contaminação agora passa a ser maior (maior valor de T_b, embora os demais continuem constantes), como esta ação só ocorre depois da percepção do contágio, suponha que este cenário só começa a partir de um determinado tempo.

Cenário 2: Melhoria nos protocolos de atendimento
Esta estratégia refere-se à capacidade de recuperação de pessoas já infectadas, influenciando assim a variável k da equação. Podemos simular esta modificação simplesmente reduzindo o tempo que leva para o paciente melhorar (menor valor de T_k). Da mesma forma que o cenário 1 este cenário só passa a ser válido depois de um determinado tempo.

### DADOS
- CENÁRIO 0: [(acessar)](https://github.com/gildo-cordeiro/PROJETO-ITP/blob/master/cenario.txt)
- CENÁRIO 1: [(acessar)](https://github.com/gildo-cordeiro/PROJETO-ITP/blob/master/cenario_2.txt)
- CENÁRIO 2: [(acessar)](https://github.com/gildo-cordeiro/PROJETO-ITP/blob/master/cenario_3.txt)

### **EXECUÇÃO:**

Para exexutar o projeto, em seu diretorio, primeiro clone o repositorio:
- `git clone https://github.com/gildo-cordeiro/PROJETO-ITP.git`

Na pasta onde foi clonado o repositorio execute: 
- `gcc -o main main.c config.c csv.c sir.c`
- `./main`

Para gerar o gráfico execute:
- `python graficos.py`
