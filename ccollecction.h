///////////////////////////////////

#pragma region DEPENDECIES

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    
#pragma endregion

///////////////////////////////////

#pragma region DEFINITIONS

    #define __MAX_INI (8)
 
#pragma endregion

///////////////////////////////////

#pragma region COLLECTION

    ///////////////////////////////////

    #pragma region typedef

        // collection
        typedef struct collection Collection; // public
        typedef struct __collection __Collection; // private

        // item
        typedef struct _item _Item; // private

    #pragma endregion
    
    #pragma region struct

        // public definition
        struct collection 
        {
            __Collection* __collection; // incomplete type, implemented in .c file
        };

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

///////////////////////////////////

#pragma region FUNCTIONS
    
    ///////////////////////////////////

    #pragma region crud

        // creation of an item and it's addition to the colleciton
        int newItem(Collection* const collection, char* pkey, ...);
        // update an item of a collection
        int updItem(Collection* const collection, char* pkey, void* updatedContent);
        // remove an item from a collection
        int remItem(Collection* const collection, char* pkey);

    #pragma endregion
    
    ///////////////////////////////////
    
    #pragma region ordering
        
        // orders the itens of a collection based on a search key according to a type and 
        // pattern provided, mapping them with the format input
        int ordCollection(char* format, Collection* const collection, int skeyIndex, ...);

    #pragma endregion

    ///////////////////////////////////
    
    #pragma region filtering

        // filters the collection accondingly to a provided pattern and search key
        int fltCollection(char* format, Collection* const collection, int skeyIndex);

    #pragma endregion
    
    ///////////////////////////////////
    
    #pragma region base
    
        // creates a new collection with a specific number of search keys
        Collection* NewCollection(int numKeys);

        // destroys a collection
        Collection* DstrCollection(Collection* collection);

    #pragma endregion
    
    ///////////////////////////////////

#pragma endregion