// script_actions.h

//!void piscarele(void){          // deprecated
//!   statusrele=!statusrele;
//!   ledrele=statusrele;
//!}


void aumentasetpoint(void){
   if(flagPlantaLigada){                                // Rotina para Aumentar Valor de SETPOINT Manualmente
      setpoint=setpoint+5;                                 // Incrementa valor de 5 graus Celsius ao SetPoint
      tempinf=setpoint-tempgap;
      tempsup=setpoint+tempgap;
   }else{
      // não incrementar nada
   }
}

void diminuisetpoint(void){                                  // Rotina para Diminuir Valor de SETPOINT Manualmente
   if(flagPlantaLigada){                                // Rotina para Aumentar Valor de SETPOINT Manualmente
      setpoint=setpoint-5;                              // Decrementa valor de 5 graus Celsius ao SetPoint
      tempinf=setpoint-tempgap;
      tempsup=setpoint+tempgap;
   }else{
      // não decrementar nada
   }
}

void tempgaprecebido(void){
   if(flagPlantaLigada){
      tempgap=atof(&sms[8]);
      //LCD
      limpa_lcd();                                        // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Novo TempGap");                // Escreve "TEXTO" no LCD
      comando_lcd(0xC0);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"TempGap:%f", tempgap); 
   }else{
      printf("-----------------------");                       // apenas informe condição de planta desligada ao celular
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
      printf(escreve_lcd,"TempAlerta:%f", tempalerta); 
   }else{
      printf("-----------------------");                       // apenas informe condição de planta desligada ao celular
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
      printf("-----------------------");                       // apenas informe condição de planta desligada ao celular
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
      printf("-----------------------");                       // apenas informe condição de planta desligada ao celular
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
      printf(escreve_lcd, "Solicit. Temp");
      comando_lcd(0xC0);                                       // Escolhe linha 2 do LCD
      printf(escreve_lcd, "Planta desligada");
   }
   conttime=8;
}

void ligaplantasp(void){
   if(flagPlantaLigada){
      setpoint=atof(&sms[5]);
      tempinf=setpoint-5;
      tempsup=setpoint+5;
      limpa_lcd();                                        // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Novo Setpoint");                // Escreve "TEXTO" no LCD
      comando_lcd(0xC0);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Setpoint:%f", setpoint);        // Exibe valor de Setpoint no LCD 
   }else{                                                 // Rotina para Ligar Planta por dispositivo móvel
      flagPlantaLigada=TRUE;
      plantaligada();
//!      mergligado();
//!      coolerligado();
      setpoint=atof(&sms[5]);
      tempinf=setpoint-5;
      tempsup=setpoint+5;
      limpa_lcd();                                        // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Acionam. remoto");              // Escreve "TEXTO" no LCD
      comando_lcd(0xC0);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Setpoint:%f", setpoint);        // Exibe valor de Setpoint no LCD 
      }
    conttime=8;
}

void ligaplantamanual(void){                              // Rotina para Ligar Planta Manualmente
   if(flagPlantaLigada){
      limpa_lcd();                                        // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"ATENCAO.");                     // Escreve "TEXTO" no LCD
      comando_lcd(0xC0);                                  // Escolhe linha 2 do LCD
      printf(escreve_lcd,"Planta ja ligada");              // Escreve "TEXTO" no LCD
   }else{ 
      flagPlantaLigada=TRUE;  
      plantaligada();
      if(setpoint!=0){                   // Verifica cond. de setpoint. Mantendo valor caso planta ligada anteriormente.
      // mantem setpoint
      }else{
         setpoint=45;                    // Configura SetPoint inicial em 45 Graus Celsius.
      }     
      tempinf=setpoint-tempgap;
      tempsup=setpoint+tempgap;
      limpa_lcd();                                        // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Acionam. local");               // Escreve "TEXTO" no LCD
      comando_lcd(0xC0);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Setpoint:%f", setpoint);        // Exibe valor de Setpoint no LCD 
   }
   conttime=8;
}

void ligaplanta(void){                              // Rotina para Ligar Planta Manualmente
   if(flagPlantaLigada){
      limpa_lcd();                                        // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"ATENCAO.");                     // Escreve "TEXTO" no LCD
      comando_lcd(0xC0);                                  // Escolhe linha 2 do LCD
      printf(escreve_lcd,"Planta ja ligada");              // Escreve "TEXTO" no LCD
   }else{ 
      flagPlantaLigada=TRUE;  
      plantaligada();
      if(setpoint!=0){                   // Verifica cond. de setpoint. Mantendo valor caso planta ligada anteriormente.
      // mantem setpoint
      }else{
         setpoint=45;                    // Configura SetPoint inicial em 45 Graus Celsius.
      }     
      tempinf=setpoint-tempgap;
      tempsup=setpoint+tempgap;
      limpa_lcd();                                        // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Acionam. remoto");               // Escreve "TEXTO" no LCD
      comando_lcd(0xC0);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Setpoint:%f", setpoint);        // Exibe valor de Setpoint no LCD 
   }
   conttime=8;
}

void desligaplanta(void){                                 // Rotina para Desligar Planta
   if(flagPlantaLigada){
      flagPlantaLigada=FALSE;
      plantadesligada();
      limpa_lcd();                                           // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                    // Escolhe linha 1 do LCD
      printf(escreve_lcd, "Planta desligada");
      comando_lcd(0xC0);                                    // Escolhe linha 2 do LCD
      printf(escreve_lcd, "Manualmente"); 
   }else{
      limpa_lcd();                                        // Função Limpa conteúdo do LCD
      comando_lcd(0x80);                                  // Escolhe linha 1 do LCD
      printf(escreve_lcd,"Status: Planta");               // Escreve "TEXTO" no LCD
      comando_lcd(0xC0);                                  // Escolhe linha 2 do LCD
      printf(escreve_lcd,"JA DESLIGADA");                 // Escreve "TEXTO" no LCD
   }                                       // A cada valor incrementado serão representados 250ms no tempo
   conttime=8;
}
