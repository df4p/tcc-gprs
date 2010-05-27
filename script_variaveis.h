// variaveis.h


// Modo de Operação do Firmware / modo protótipo 0 (default) / Kit de testes modo 1
int   firmwaremode=0;

// Gerais
#locate  rc_reg=0x1A

#byte porta=0x05
#byte portb=0x06
#byte portc=0x07
#byte txsta=0x98
#byte rcsta=0x18

#bit  bt1=portb.0
#bit  bt2=portb.1
#bit  bt3=portb.2
#bit  bt4=portb.3
#bit  bt5=portb.4
#bit  ledalerta=portb.5
#bit  ledmerg=portb.6
#bit  ledcooler=portb.7

#bit  ledrele=portc.0
#bit  buzzer=portc.1
#bit  cooler=portc.2
#bit  ledon=portc.3
#bit  rele=portc.4
#bit  merg=portc.5


// Variaveis e Constantes
unsigned int contTimeOut=0;
char  chegou;                    // variavel que recebe todos os valores que chegam da serial
int   cont=0;                    // int responsavel por contagem de caracteres recebidos
char  fim;                       // caracter que passa final de mensagem SMS  
int   tipoComando=0;             // Tipo de comando recebido (CMGR, CMTI, OK ou outro configurado)
char  sms[16];                   // Variavel que contem a mensagem SMS recebida do modem
int   contSMS=0;                 // Contador de caracteres da SMS
char  ok[]={"OK"};               // Variavel que determina o conteúdo de uma mensagem tipo OK
char  cmti[]={"+CMTI"};          // Variavel que determina o conteúdo de uma mensagem tipo CMTI
char  cmgr[]={"+CMGR"};          // Variavel que determina o conteúdo de uma mensagem tipo CMGR
int   cmtiIndex=0;
char  flagSMS=FALSE;             // Flag responsável pela detecção da mensagem SMS.
int   flagPlantaLigada=FALSE;    // Flag que armazena condicao da planta


float tensao;
float setpoint=0;                // Setpoint de trabalho da planta
float setpointgap=0.5;           // Intervalo de incremento e decremento do Setpoint
float temp=0;                    // Temperatura real da planta
float tempinicial=25;            // Temperatura padrao para inicio de atividades da planta
char  fone[]={"6296899991"};     // Numero inicial de telefone celular que envia comando
float tempgap=5;                 // Intervalo entre Temp Superior e Temp Inferior 
float tempalerta=39.5;           // Valor a ser somado a tempgap que acarretará o alerta
int   conttemp=0;                // Contador de avaliações de temperatura para média de leituras
int   statusrele=0;              // estado do Rele

// SMS
char  smsplantaon[]={"plantaon"};
char  smsplantasp[]={"ponstp: "};
char  smsplantaoff[]={"plantaoff"};
char  smstemp[]={"temprec"};
char  smstempalerta[]={"tmpwrn: "};
char  smstempgap[]={"tmpgap: "};
char  smsreleon[]={"releon"};
char  smsreleoff[]={"releoff"};


// Define's para ações

#define  buzzerligado() buzzer=1; ledalerta=1     // Buzzer em 0 = Kit e 1 = prototipo
#define  buzzerdesligado() buzzer=0; ledalerta=0

#define  coolermaximo() set_pwm1_duty(123); ledcooler=1
#define  coolermedio() set_pwm1_duty(80); ledcooler=1
#define  coolerdesligado() set_pwm1_duty(0); ledcooler=0
#define  mergligado() merg=1; ledmerg=1
#define  mergdesligado() merg=0; ledmerg=0
#define  releligado()   ledrele=1; rele=1
#define  reledesligado()   ledrele=0; rele=0
#define  plantaligada() ledon=1; flagPlantaLigada=TRUE
#define  plantadesligada() ledon=0; ledrele=0; merg=0; ledmerg=0; set_pwm1_duty(0); ledcooler=0;  buzzer=1; ledalerta=0; flagPlantaLigada=FALSE
#define  alterasetpoint TRUE
#define  naoalterasetpoint FALSE
#define  local  TRUE
#define  remoto FALSE





// deprecated
//float tempsup;                   // Temperatura máxima para ação da planta
//float tempinf;                   // Temperatura mínima para ação da planta
//char  smsligaralerta[]={"alertaon"};
//char  smsdesligaralerta[]={"alertaoff"};   
//char  smsreleon[]={"releon"};
//char  smsreleoff[]={"releoff"};
