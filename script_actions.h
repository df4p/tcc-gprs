// script_actions.h

void mudasetpoint(float novovalor){
   setpoint=novovalor;
}

void aumentasetpoint(void){
   if(flagPlantaLigada){                           // Rotina para Aumentar Valor de SETPOINT Manualmente
      mudasetpoint(setpoint+5);
   }
}


void diminuisetpoint(void){                             // Rotina para Diminuir Valor de SETPOINT Manualmente
   if(flagPlantaLigada){                                // Rotina para Aumentar Valor de SETPOINT Manualmente
      mudasetpoint(setpoint-5);
   }
}


void checamodoop(void){
     firmwaremode=!firmwaremode;
     limpa_lcd();                                        // Função Limpa conteúdo do LCD
     comando_lcd(0x80);                                  // Escolhe linha 1 do LCD
     printf(escreve_lcd,"Modo Sensor");                // Escreve "TEXTO" no LCD
     comando_lcd(0xC0);                                  // Escolhe linha 2 do LCD
     printf(escreve_lcd,":%u", firmwaremode);
}

void tempgaprecebido(void){
   if(flagPlantaLigada){
      tempgap=atof(&sms[8]);
      
      //LCD
      limpa_lcd();                                        // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Novo TempGap");                 // Escreve "TEXTO" no LCD
      comando_lcd(0xC0);                                  // Escolhe linha 2 do LCD
      printf(escreve_lcd,"TempGap:%f  ", tempgap); 
   }else{
      // apenas informe condição de planta desligada ao celular
      printf("\n\r");
      printf("AT+CMGS=\"+55%s\"",fone);
      printf("\n\r");
      printf("Fatec TCC\n\r");
      printf("Caso queira ligar por favor enviar setpoint ou comando ligar.\n\r");
      printf("%c", fim);
      delay_ms(200);
      
      // LCD
      limpa_lcd();                                             // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                       // Escolhe linha 1 do LCD
      printf(escreve_lcd, "Ped. TempGap");
      comando_lcd(0xC0);                                       // Escolhe linha 2 do LCD
      printf(escreve_lcd, "Planta desligada");
   }     
   conttime=8;
}



void tempalertarecebido(void){
   if(flagPlantaLigada){
      tempalerta=atof(&sms[8]);
      //LCD
      limpa_lcd();                                        // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Novo TempAlerta");                // Escreve "TEXTO" no LCD
      comando_lcd(0xC0);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"TempAlerta:%f    ", tempalerta); 
   }else{
      printf("\n\r");
      printf("AT+CMGS=\"+55%s\"",fone);
      printf("\n\r");
      printf("Fatec TCC\n\r");
      printf("Status da Planta: DESLIGADA.\n\r");
      printf("Caso queira ligar por favor enviar setpoint ou comando ligar.\n\r");
      printf("%c", fim);
      delay_ms(200);
      // LCD
      limpa_lcd();                                             // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                       // Escolhe linha 1 do LCD
      printf(escreve_lcd, "Ped. TempAlerta");
      comando_lcd(0xC0);                                       // Escolhe linha 2 do LCD
      printf(escreve_lcd, "Planta desligada");
   }     
   conttime=8;
}



void enviatemp(void){                             
   if(flagPlantaLigada){
      //LCD
      limpa_lcd();                                             // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                       // Escolhe linha 1 do LCD
      printf(escreve_lcd, "Env: %s", fone);
      comando_lcd(0xC0);                                       // Escolhe linha 2 do LCD
      printf(escreve_lcd, "Temp: %f",temp);
      conttime=2;                                              // A cada unidade incrementada o valor de tempo será de 250ms
      //SMS
      printf("\n\r");
      printf("AT+CMGS=\"+55%s\"",fone);
      printf("\n\r");
      conttime=1; 
      printf("Fatec TCC\n\r");
      printf("Temperatura: %f", temp);
      printf("\n\r");
      conttime=1; 
      printf("%c", fim);    
   }else{
      // SMS
      // apenas informe condição de planta desligada ao celular
      printf("\n\r");
      printf("AT+CMGS=\"+55%s\"",fone);
      printf("\n\r");
      printf("Fatec TCC\n\r");
      printf("Status da Planta: DESLIGADA.\n\r");
      printf("Caso queira ligar por favor enviar setpoint ou comando ligar.\n\r");
      printf("%c", fim);
      conttime=1; 
      // LCD
      limpa_lcd();                                             // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                       // Escolhe linha 1 do LCD
      printf(escreve_lcd, "Solicit. Temp");
      comando_lcd(0xC0);                                       // Escolhe linha 2 do LCD
      printf(escreve_lcd, "Planta desligada");
   }
   conttime=8;
}



void ligaplanta(boolean flagAlteraSetpoint, boolean flagTipoAcao){
   if(flagAlteraSetpoint==alterasetpoint){
      mudasetpoint(atof(&sms[8]));
   }else{
      if(setpoint!=0){ 
         // do nothing
      }else{
         mudasetpoint(tempinicial);
      }
      limpa_lcd();                                        
   }
   
   if(flagPlantaLigada){
      if(flagTipoAcao==local){
         //MsgLocal
         comando_lcd(0x80); 
         printf(escreve_lcd,"Planta ja ligada"); 
      }else{
         //MsgRemota
         comando_lcd(0x80); 
         printf(escreve_lcd,"Planta ja ligada"); 
      }
   }else{
      plantaligada();
      if(flagTipoAcao==local){
         //MsgLocal
         comando_lcd(0x80); 
         printf(escreve_lcd,"Acionam. local  ");
      }else{
         //MsgRemota
         comando_lcd(0x80);
         printf(escreve_lcd,"Acionam. remoto ");             
      }
   }
   comando_lcd(0xC0);                                
   printf(escreve_lcd,"Setpoint:%f   ", setpoint);        
  
  conttime=8;
}      


void desligaplanta(boolean flagTipoAcao){
   if(flagPlantaLigada){
      plantadesligada();
      limpa_lcd();  
      if(flagTipoAcao==local){
         //MsgLocal
         comando_lcd(0x80); 
         printf(escreve_lcd,"Desacion. local "); 
      }else{
         //MsgRemota
         comando_lcd(0x80); 
         printf(escreve_lcd,"Desacion. remoto"); 
      }
   }else{ 
      if(flagTipoAcao==local){
         //MsgLocal
         comando_lcd(0x80); 
         printf(escreve_lcd,"Planta ja deslig");
      }else{
         //MsgRemota
         comando_lcd(0x80);
         printf(escreve_lcd,"Planta ja deslig");      
      }
   }                                       
   comando_lcd(0xC0);                                 
   printf(escreve_lcd,"StandBy         ");  
   conttime=8;
}



void piscarele(void){   
   statusrele=!statusrele;
   ledrele=statusrele;
}


/* void mostravalores(void){                            
   if(flagPlantaLigada){ 
      printf("\n\r");
      printf("temp: %f\"",temp);
      printf("\n\r");
      printf("setpoint: %f\"",setpoint);
      printf("\n\r");
      printf("tempgap: %f\"",tempgap);
      printf("\n\r");
      printf("tempalerta: %f\"",tempalerta);
      printf("\n\r");
      printf("setpointgap: %f\"",setpointgap);
      printf("\n\r");
   }
}
*/
