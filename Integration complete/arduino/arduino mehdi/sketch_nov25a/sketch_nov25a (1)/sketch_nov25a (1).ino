#include <LiquidCrystal_I2C.h> 
// En cas de non fonctionnement, mettez la ligne 8 en
// commentaire et retirez le commentaire à la ligne 9.
LiquidCrystal_I2C lcd(0x27, 20, 4); // ligne 8
//LiquidCrystal_I2C lcd(0x3F,20,4); // ligne 9
//LiquidCrystal_I2C lcd(0x3F,16,2); // ligne 9



char data; 
 String date;  
  String id;  

//char id[20];
void setup()
{
lcd.init(); // initialisation de l'afficheur
Serial.begin(9600);

}
void loop()
{
lcd.backlight(); // active le rétro-éclairage



lcd.setCursor(0, 0); // se positionner à la première ligne
lcd.print(" Cloud FM");  // Afficher le mot 'carte'
lcd.setCursor(0,1);  // se positionner à la deuxième ligne
lcd.print(" Bienvenue!"); // Afficher le mot 'Arduino'





 if (Serial.available()){     
  
      data=Serial.read();  
   //date = Serial.readString( );  
id = Serial.readString( );  
 date = Serial.readString( );  
       if(data=='1') 
        {
          lcd.clear();
      lcd.setCursor(0,0);
    
      lcd.print("ajout de l'id:");
       lcd.setCursor(0,1);
      lcd.print(id);
      delay(5000);
      
         lcd.clear();
      data=7;
        }  

        
       else if(data=='0')
       {
         lcd.clear();
       lcd.setCursor(0,0);
      lcd.print("supprimation de  de l'id: ");
       lcd.setCursor(0,1);
      lcd.print(id);
       delay(5000);
       
         lcd.clear();
        data=7;
       }   

else if(data=='2')
       {
         lcd.clear();
     lcd.setCursor(0,0);
      lcd.print("modification de l'id: ");
       lcd.setCursor(0,1);
      lcd.print(id);
       delay(5000);
       
         lcd.clear();
        data=7;
       }   


else if(data=='3')
       {
        
 
         lcd.clear();
     lcd.setCursor(0,0);
      lcd.print("affichage de lid:");
       lcd.setCursor(0,1);
      lcd.print(id);
       delay(5000);
        lcd.setCursor(0,0);
        data=7;
         
         lcd.clear();
        }

else if(data=='4')
       {
        
 
         lcd.clear();
     lcd.setCursor(0,0);
      lcd.print(id);
       lcd.setCursor(0,1);
      lcd.print(date);
       delay(5000);
        lcd.setCursor(0,0);
        data=7;
         
         lcd.clear();
        }


      }



}