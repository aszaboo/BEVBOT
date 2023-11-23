/*
This file contains all functions and constants used to take orders
*/

// takes the customers order
string takeOrder()
{

    string order_kind;

    displayString(3, "Please scan your order");

    do 
    {
    if(SensorValue[S1] == (int)colorRed) 
    {
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
    else
    displayString(3, "Sorry we do not have that drink");

    } while (order_kind != "Coke" || order_kind != "Raspberry Lemonade" || order_kind != "Lemonade");
      
    return order_kind;
    
}


// makes a bell noise and delivers the order to the table
void orderUp(int tableNumber, string order_kind) 
{
        // wait for enter button to be released (p2)
	while(!getButtonPress(buttonEnter)) 
  {
    displayString(3, "%s", order_kind);
	}

	while(getButtonPress(buttonEnter)) {}
  wait1MSec(200);
  goToTable(tableNumber);
}

