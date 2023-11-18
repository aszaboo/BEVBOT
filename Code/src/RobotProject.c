#include <.../include/config.c>
#include <.../include/drive_functions.c>
#include <.../include/order_functions.c>
#include <.../include/std_functions.c>

task main() 
{
    while(time1[t1] < TIME_OUT) 
    {
        // while there is no IRBeacon signal do nothing
        while(!getIRBeaconDirection(s4)) {}
        
        // locating and driving to table
        table_number = locateTable(getIRBeaconDirection(s4));
        goToTable(table_number, table_locations);

        // taking the customers order
        takeOrder();

        // returining to the table
        returnToBase(table_number);

        // wait for order completion'
        orderUp(table_number);

        // lifting gripper
        






        
    }
    





}



