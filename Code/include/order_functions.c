/*
This file contains all functions and constants used to take orders
*/

// takes the customers order
void takeOrder()
{

    string order_kind = " ";

    displayString(3, "Please scan your order");

    while(order_kind == " "){
    if(SensorValue[S1] == (int)colorRed) {
    order_kind = "Coke";
    }
    else if(SensorValue[S1] == (int)colorBlue)
    {
    order_kind = "Raspberry Lemonade";
    }
    else if(SensorValue[S1] == (int)colorYellow)
    {
    order_kind = "Lemonade";
    }
    wait1Msec(2000);

  }
//This if statement should go outside the function to ensure the string will stay while drivin back
  if(order_kind == "Coke" || order_kind == "Raspberry Lemonade" || order_kind == "Lemonade")
    {
        displayString(3, order_kind);
        wait1Msec(10000);
    }else
    {
        displayString(3, "No valid order");
        wait1Msec(10000);
    }

// makes a bell noise and delivers the order to the table
void orderUp(int tableNumber) {
        while(!SensorValue[S1]) {}
        wait1MSec(200);
        goToTable(tableNumber);
    }
}

