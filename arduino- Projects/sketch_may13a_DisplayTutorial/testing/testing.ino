int temp1;
int temp2;
int count_value;

void setup() {
  // put your setup code here, to run once:
  temp1 = 0;
  temp2 = 0;
  count_value = 0;
  pinMode(13, OUTPUT);
}

void loop() {

  if(temp1 == 0 || temp2 == 0){
    count_value++;
  }
  // put your main code here, to run repeatedly:
//  if (temp1 == 0 && temp2 == 0)
//  {
//     count_value++;
//   
//  } else 
//  {
//    if (temp1 == 0 || temp2 == 0)
//    {
//       count_value++;      
//    }  
//   
//  }

  if (count_value == 1) {
   
    digitalWrite(13, HIGH);  // sets the digital pin 13 off
    delay(30000);
  }else if(count_value == 2)
  {
    digitalWrite(13, LOW);  // sets the digital pin 13 off
    delay(30000);
    
  }
  
}
