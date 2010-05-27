   set_tris_a(0b00111111);
   set_tris_b(0b00011111);
   set_tris_c(0b10000000);
   set_tris_d(0b00000000);
   set_tris_e(0b00000000);
  
   porta=0;
   portb=0;
   portc=0;
   portd=0;
   porte=0;
   
   fim=26;                                        // caracter sinaliza fim da msg pronta para envio no modem.
   inicializa_lcd();                              // Inicializa LCD
   limpa_lcd();                                   // Função Limpa conteúdo do LCD
   comando_lcd(0x80);                             // Escolhe linha 1 do LCD
   printf(escreve_lcd,"TCC Fatec 2010");              // Escreve "TEXTO" no LCD
   comando_lcd(0xC0);                             // Escolhe linha 2 do LCD
   printf(escreve_lcd,"Aut. Industrial");         // Escreve "TEXTO" no LCD   
   printf("ATE0\n\r");                             // Comando para desabilitar ECHO do modem GPRS
   printf("AT+CMGF=1\n\r");                        // Seta modem para repassar mensagens em caracteres na forma texto
//   printf("AT+CMGD=1\n\r");                        // Deleta qualquer mensagem guardada no modem para que nao haja erros na inicializacao
   
   enable_interrupts(global);                    // habilita interrupções globais
   enable_interrupts(int_rda);                   // habilita interrupção rda
   enable_interrupts(int_timer1);
   limpa_msg();                                  // Função Limpa conteúdo do LCD
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4_AN5);
   setup_adc(ADC_CLOCK_DIV_32);  
   setup_timer_1 ( T1_INTERNAL | T1_DIV_BY_8 );   // timer para display de temperatura
   set_timer1(851);        
   setup_timer_2(T2_DIV_BY_16,124,1);             //frequencia de 1kHz
   setup_ccp1(CCP_PWM);                           // CCP1 para PWM
 
   coolerdesligado();                             // Seta o PWM em Zero para não deixar o Cooler ligado desde o início
   mergdesligado();
   buzzerdesligado();
  

