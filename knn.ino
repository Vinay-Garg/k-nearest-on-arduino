// Implementation of KNN //
#include "dataset.h"
//#include "dataset2.h"
#include "functionKNN.h"

double data[co];
int k=11;
long actual = 0, previous = 0;

// Given the identifiers extracted characters and converts them to double
void data_extracted(String str, double data[], char dlm[]){
  
  String auxstr = "";
  int posdlm[5], tamstr = 0;
  int i= 0, j = 0;
  
  // search for character identification
  posdlm[0] = str.indexOf(dlm[0]); // (
  posdlm[1] = str.indexOf(dlm[1]); // ,
  posdlm[2] = str.indexOf(dlm[1], posdlm[1] + 1); // ,
  posdlm[3] = str.indexOf(dlm[1], posdlm[2] + 1); // ,
  posdlm[4] = str.indexOf(dlm[2]); // )
    
  for(j=0; j<co; j++){
    // extracting numerical data
    for(i=posdlm[j]+1; i<posdlm[j+1]; i++){
      auxstr = auxstr + str[i];  
    }

    // convert to double
    int y = auxstr.length();
    char buf[y+1];
    auxstr.toCharArray(buf, y+1);
    data[j] = atof(buf);
    
    //Serial.println(data[j],3);
    auxstr=""; // auxiliary reset
    }      
}


void prints(double data[], int clase){  
  Serial.println("-----------------------------------------------");
  Serial.print(Atr[0]); Serial.print(": "); Serial.print(data[0],3); Serial.println(" cms");
  Serial.print(Atr[1]); Serial.print(": "); Serial.print(data[1],3); Serial.println(" cms");
  Serial.print(Atr[2]); Serial.print(": "); Serial.print(data[2],3); Serial.println(" cms");
  Serial.print(Atr[3]); Serial.print(": "); Serial.print(data[3],3); Serial.println(" cms");
  Serial.print(" >> Class: "); Serial.println(classesSt[clase]);
}


void setup() {
  Serial.begin(9600); 
  //delay(500);
  Serial.println("CLASSIFICATION with \"K nearest neighbour method\" \n implemented by vinay ");
  //delay(500);
}

void loop() {
  if(Serial.available()){       
    String str = Serial.readStringUntil('\n');  
    data_extracted(str, data, "{,}");    

  // print
//int l=0;
//    prints(data, l);
 
    previous = millis();             
//    // find the class with k neighbors
    int cl = classify_KNN((double*)attributes, classesNo, data, k, fi, co); 
    actual = millis();
//  Serial.print(cl);
//    // print
    prints(data, cl);
    Serial.print("Time: "); Serial.print(actual-previous); Serial.println(" ms");   
  }
}


