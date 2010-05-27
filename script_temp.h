// script_temp.h

void checaTemperatura(void){
   
   if(flagPlantaLigada){
      set_adc_channel(2);
      delay_us(20); 
      conttemp=0;
      temp=0;
      
      for(;conttemp<10;conttemp++){       // media de temperatura em 10 leituras para maior estabilidade
         tensao=read_adc();
         tensao=tensao*5;
         tensao=tensao/1023;
         
         // Escolhendo modo de temperatura pelo modo de operação do firmware configurado em variaveis
         if(firmwaremode==0){
           temp=(90*tensao);  // Temperatura para operação com protótipo e sensor de temperatura PT-100
           temp=temp-78.39;
           temp=temp/3.049;
         }else{
           temp+=tensao*10;   // Temperatura para operação com sistema de Temperatura do Kit de Desenvolvimento 
         }
      }
   
      if(conttime==0){
         limpa_lcd();                                    // Função Limpa conteúdo do LCD
         comando_lcd(0x80);                              // Escolhe linha 1 do LCD
         printf(escreve_lcd, "Temp: %f",temp);           // Envia valor da temperatura para LCD
         comando_lcd(0xC0);                              // Escolhe linha 2 do LCD
         printf(escreve_lcd, "Setpoint: %f",setpoint);   // Envia valor de setpoint para LCD
         conttime=8;                                     // A cada unidade incrementada o valor de tempo será de 250ms
      }
      
      
       if(temp>(setpoint+setpointgap)){
         if(temp>(setpoint+setpointgap+4.5)){
            if(temp>(setpoint+setpointgap+tempalerta)){
               buzzerligado();
            }else{
               buzzerdesligado();
            }
            coolermaximo();
         }else{
            coolermedio();         
         }      
         mergdesligado();    
       }else{
         if(temp<(setpoint-setpointgap)){
            if(temp<(setpoint-setpointgap-tempalerta)){
               buzzerligado();
            }else{
               buzzerdesligado();
            }
            mergligado();
            coolerdesligado();
         }else{
            coolerdesligado();
            mergdesligado();
            buzzerdesligado();
         }
       }
             
   
   }else{ // status de planta desligada

      buzzerdesligado();
      mergdesligado();
      coolerdesligado();
   }

}
