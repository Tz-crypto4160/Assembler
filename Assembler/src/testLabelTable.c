/*
 * Test Driver to test the functions to access and manipulate a label table.
 * It includes the following tests:
 * - Printing an empty table
 * - Searching an empty table
 * - Printing and searching a populated static table
 * - Initializing a dynamic table
 * - Adding labels to a dynamic table (normal cases)
 * - Searching a dynamic table (found / not found)
 * - Adding a duplicate label (boundary/error case)
 * - Adding enough labels to trigger table resizing (boundary case)
 *
 *      Author:  Taiki Sawamata
 *      with assistance from: 
 *
 *      Creation Date:  02/14/2026
 *      modified: Modification_Date        reason
 *      modified: Modification_Date        reason
 */

#include "assembler.h"

static void testSearch(LabelTableArrayList * table, char * searchLabel);

int main(int argc, char * argv[])
{
    /* Process command-line argument (if provided) for
     *    debugging indicator (1 = on; 0 = off).
     */
    (void) process_arguments(argc, argv);

    /* Create 2 tables, one static and one dynamic, for testing purposes.
     * We can test printLabels and findLabelAddr with a simple static table.
     */
    printf("===== Testing with static tables =====\n");

    /* Create an empty static label table. */
    LabelTableArrayList staticEmptyTable;      /* table with 0 static entries */
    staticEmptyTable.capacity = 0;
    staticEmptyTable.nbrLabels = 0;
    staticEmptyTable.entries = NULL;

    /* Create a static array of label entries for initial testing. */
    LabelEntry staticEntries[5];
    staticEntries[0].label = "Label1";
    staticEntries[0].address = 1000;
    staticEntries[1].label = "Label2";
    staticEntries[1].address = 1004;

    /* Initialize staticTable2 to use the static array above. */
    LabelTableArrayList staticTable2;      /* table with static entries */
    staticTable2.capacity = 5;
    staticTable2.nbrLabels = 2;
    staticTable2.entries = staticEntries;

    /* --- test execution for static tables --- */
    printf("\n[Test] Empty Static Table:\n");
    printLabels(&staticEmptyTable);
    testSearch(&staticEmptyTable, "Label1");

    printf("\n[Test] Populated Static Table:\n");
    printLabels(&staticTable2);
    testSearch(&staticTable2, "Label1"); /* should be found (1000) */
    testSearch(&staticTable2, "Label3"); /* not be found (-1) */

    printf("\n===== Testing with dynamic table =====\n");

    /* Initialize dynamicTable as a dynamic (changeable size) table. */
    LabelTableArrayList dynamicTable;      /* table with dynamic entries */
    tableInit(&dynamicTable);

    /* --- dynamic table --- */
    printf("\n[Test] Initialized Dynamic Table (Should be empty):\n");
    printLabels(&dynamicTable);

    printf("\n[Test] Adding 3 labels to Dynamic Table:\n");
    addLabel(&dynamicTable, "main", 4000);
    addLabel(&dynamicTable, "loop", 4004);
    addLabel(&dynamicTable, "end", 4008);
    printLabels(&dynamicTable);

    printf("\n[Test] Searching Dynamic Table:\n");
    testSearch(&dynamicTable, "loop"); /* should be found (4004) */
    testSearch(&dynamicTable, "start"); /* not be found (-1) */

    printf("\n[Test] Boundary: Adding a duplicate label (should print error):\n");
    addLabel(&dynamicTable, "main", 5000); /*Should print an error message because it already exists */

    printf("\n[Test] Boundary: Triggering table resize (adding beyond capacity):\n");
    /* Add many labels to verify initial capacity and resizing behavior*/
    addLabel(&dynamicTable, "L1", 4012);
    addLabel(&dynamicTable, "L2", 4016);
    addLabel(&dynamicTable, "L3", 4020);
    addLabel(&dynamicTable, "L4", 4024);
    addLabel(&dynamicTable, "L5", 4028);
    addLabel(&dynamicTable, "L6", 4032);
    addLabel(&dynamicTable, "L7", 4036);
    addLabel(&dynamicTable, "L8", 4040); /*this makes 11 total entries, ensuring a resize*/
    printLabels(&dynamicTable);
    
    printf("\n===== All Tests Completed =====\n");
    return 0;
}


/*
 * testSearch tests the findLabelAddr function, printing out the label being
 * searched for and either the address where it was found or, if it was
 * not found, an address of -1 and a message that the label was not in
 * the table.  
 *  @param  tablePtr     a pointer to the table through which to search
 *  @param  searchLabel  the label to search for
 */
static void testSearch(LabelTableArrayList * tablePtr, char * searchLabel)
{
    int address;

    printf("Looking for %s...\n", searchLabel);

    address = findLabelAddr(tablePtr, searchLabel);
    if ( address != -1 ) 
    {
        printf("\tthe address is %d.\n", address);
    } 

    else 
    {
        printf("\tthe address is %d.\n", address);
        printf("\tThe label you're looking for does not exist.\n");
    }
}
