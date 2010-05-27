// int_rda.h

#int_rda
void  recebido(void){
//!-----------------------------------------------------------------------------------------------------------
// Recebe os valores de rc_reg e incrementa as variaveis msg e cont 
   chegou=rc_reg;                      // A variavel chegou recebe os valores do registrador
   if(chegou!='\n'&&chegou!='\r'){     // Checa caracteres de chegou diferentes de \r e \n
      msg[cont]=chegou;                // msg é a variavel que recebe os caracteres
      cont=cont+1;                     // incrementa a variável cont para os caracteres
      if(flagSMS){                     // Caso identificado CMGR - Aciona FLAG para registrar a Mensagem SMS
         sms[contSMS]=chegou;          // Caso valida recebe valor da variavel chegou
         contSMS++;                    // Incrementa variavel contSMS formando a propria SMS recebida no modem
         }
   }
   
//!-----------------------------------------------------------------------------------------------------------
//Rotina que checa o CONT
   if(chegou==0x0A&&cont!=0){          // Caso tenha chegado ao fim da linha
      msg[cont]='\0';                  // Zera a variavel msg
      if(flagSMS){                     // Checa se flagSMS é TRUE
         cont=0;                       // Zera o cont
         sms[contSMS]='\0';            // Zera o contSMS
         flagSMS=FALSE;                // Volta flagSMS ao estado inicial FALSE
      }
      if(cont==2){                     //Testa se 2 vezes 0x0A é refetente a AT OK          
         if(strncmp(msg,ok,2)==0){     // Compara a string msg ao valor de OK
            tipoComando=1;             // Caso seja igual OK seta tipoComando para 1
         }        
      }
      if(cont>8 && cont<16){           //Teste se 2 vezes 0x0A é referente a +CMTI  
         if(strncmp(msg,cmti,5)==0){   // Compara string msg ao valor de +CMTI    ptr=strchr (s1,  c)
            cmtiIndex = atoi(strchr (msg,  ',')+1);
            tipoComando=2;             // Caso afirmativo seta tipoComando para 2
         }        
      }
      if(cont>46){         
         if(strncmp(msg,cmgr,5)==0){   // Compara string msg ao valor de +CMGR
            strncpy (fone,strchr (msg,',')+3, 10);
            tipoComando=3;             // Caso afirmativo seta tipoComando para 3
            contSMS=0;                 // Zera contSMS
            flagSMS=TRUE;              // Seta flagSMS para verdadeiro
         }        
      }
      cont=0;                          // Zera variável cont.
   }   
}
