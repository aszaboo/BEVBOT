/*
This file contains all functions and constants used to take orders
*/

// takes the customers order
void takeOrder() 
{
    string order_kind = " ";

    do {

    displayString(3, "Please scan your order");

    if(SensorValue[S3] = (int)colorRed) {
    order_kind = "Coke";

    else if(SensorValue[S3] = (int)colorBlue)
    order_kind = "Raspberry Lemonade";

    else if(SensorValue[S3] = (int)colorYellow)  
    order_kind = "Lemonade";

    else displayString(3, "Not a valid order type");

    } while(order_kind = " ");

    } // takeOrder

    displayString(3, "Please make %f" order_kind);
    
}

// makes a bell noise and delivers the order to the table
void orderUp(bool touchSensorInput, int tableNumber) {
        while(!touchSensorInput) {}
        wait1MSec(200);
        goToTable(tableNumber);
    }
}

