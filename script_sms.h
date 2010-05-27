 // script_sms.h
 
void checaSMS(void){
 
switch(tipoComando){
      case 1: // Caso msg identificada como ATOK
         tipoComando=0;     
      break;
      case 2: // Caso msg identificada como CMTI
         tipoComando=0;
         limpa_lcd();
         comando_lcd(0x80);
         printf(escreve_lcd, "SMS Recebido");
         printf("AT+CMGR=%i\n\r", cmtiIndex);
         conttime=4;
      break;
      case 3: // Caso msg identificada como CMGR
         tipoComando=0;
         limpa_lcd();
         comando_lcd(0x80);
         printf(escreve_lcd, "+CMGR");
         comando_lcd(0xC0);  
         while(flagSMS&&contTimeOut!=0){
            contTimeOut--;
            conttime=4;
         }
         printf(escreve_lcd, "SMS: %s",sms);      //!-Rotina de escrita e tratamento de SMS
         //delay_ms(50);
         conttime=6;  
         printf("%s",sms);                        //Imprime SMS recebida para serial
         printf("\n\r");
         printf("AT+CMGD=%i\n\r", cmtiIndex);
         printf("AT+CMGF=1\n\r");
       
       
         if(strcmp(sms, smsplantaon)==0){        
           ligaplanta(naoalterasetpoint, remoto); //acao executada
         }
         
         if(strncmp(sms, smsplantasp,8)==0){         
           ligaplanta(alterasetpoint, remoto); //acao executada
         }
         
         if(strcmp(sms, smsplantaoff)==0){          
           desligaplanta(remoto); //acao executada
         }
         
         if(strcmp(sms, smstemp)==0){         
           enviatemp(); //acao executada
         }
         
         if(strncmp(sms, smstempgap,8)==0){
           tempgaprecebido(); //acao executada
         }
         
         if(strncmp(sms, smstempalerta,8)==0){ 
           tempalertarecebido(); //acao executada
         }
         
         if(strcmp(sms, smsreleon)==0){         
           releligado(); //acao executada
         }
         if(strcmp(sms, smsreleoff)==0){         
           reledesligado(); //acao executada
         }
         
         
// DEPRECATED ACTIONS         
         
//         if(strcmp(sms, smsligaralerta)==0){      
//           buzzerligado();  //acao executada
//         }
        
//         if(strcmp(sms, smsdesligaralerta)==0){ 
//           buzzerdesligado(); //acao executada
//         }
         
//         if(strcmp(sms, smsreleon)==0){       
//           releligado(); //acao executada
//         }
            
//         if(strcmp(sms, smsreleoff)==0){            
//           reledesligado(); //acao executada
//         }


     break;
     default:  
   }
}
