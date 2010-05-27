//TCC Fatec SENAI GO
//Automação Industrial - Turma 05
//Danilo F. A. Pires / Jorge Wanderson Barbosa / Raphael de Paula Oliveira
//Subj: Sistema de comunicação por GPRS para controle remoto industrial através do envio de SMS por celulares.

#include "device.h"                 // chamada ao script do dispositivo
#include <stdlib.h>                 // chamada de biblioteca stdlib
#include <math.h>                   // chamada de biblioteca de operacoes matematicas
#include "lcd.h"                    // chamada a biblioteca de LCD

#include "script_variaveis.h"       // script com as variaveis do sistema
#include "script_int_rda.h"         // script que trata a interrupcao responsavel pela serial
#include "script_int_timer1.h"      // script que trata timer1 responsável por temporizador
#include "script_actions.h"         // script de acoes do sistema


void main(){
   #include "script_startup.h"         // script de inicializacao de hardware

   while(1){
   #include "script_sms.h"            // script que trata as mensagens sms recebidas

   #include "script_temp.h"            // logica de tratamento de temperatura
   #include "script_botoes.h"          // script com logica de acao de botoes

   }
}
