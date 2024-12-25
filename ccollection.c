///////////////////////////////////

#pragma region DEPENDECIES 

    #include "ccollection.h"

#pragma endregion

///////////////////////////////////

#pragma region COLLECTION 

    ///////////////////////////////////

    #pragma region struct 

        // private
        struct __collection 
        {
            // properties
            int size;
            int limit;
            int const numSrchKeys;
            // array of itens
            __Item *itens; 
        };

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

///////////////////////////////////

#pragma region ITEM 

    ///////////////////////////////////
    
    #pragma region struct 

        struct __item 
        {
            // primary key, used for crud operations
            char* pkey;
            // array for the search keys
            void **skeys;
            // logical exclusion
            char active;
            // generic pointer to content
            void *content;
        };

    #pragma endregion
    
    ///////////////////////////////////

#pragma endregion

///////////////////////////////////

#pragma region HEADER

    static __Item newItem(void *const content, char *pkey, void *skeys[]);
    static int addItem(Collection *const collection, __Item item);

#pragma endregion

///////////////////////////////////

#pragma region FUNCTIONS

    ///////////////////////////////////
    
    #pragma region crud

        int addNewItem(Collection *const collection, void *const content, char *pkey, ...)
        {
            int result;

            if (collection->__collection->numSrchKeys > 0)
            {
                va_list vl;
                va_start(vl, pkey);

                void *skeys[collection->__collection->numSrchKeys];

                for (int i = 0; i < collection->__collection->numSrchKeys; i++)
                    skeys[i] = va_arg(vl, void*);
                
                result = addItem(collection, newItem(content, pkey, skeys));
            }
            else 
                result = addItem(collection, newItem(content, pkey, NULL));  

            return result;
        }

    #pragma endregion

    ///////////////////////////////////

    #pragma region ordering

    #pragma endregion

    ///////////////////////////////////

    #pragma region filtering

    #pragma endregion

    ///////////////////////////////////
    
    #pragma region private 

    static int addItem(Collection *const collection, __Item item)
    {
        // verifying the limit and actual size
        if (collection->__collection->size == collection->__collection->limit)
        {
            // realloc and update limit
            return 0;
        }

        // assign the new item to it's location
        collection->__collection->itens[collection->__collection->size] = item;
        collection->__collection->size++;

        // return success
        return 1;
    }

    static __Item newItem(void *const content, char* pkey, void* skeys[])
    {
        // memory allocation
        __Item item = {
            pkey, 
            skeys, 
            __I_ACTIVE, 
            content
        };

        // returns the item
        return item;
    }

    #pragma endregion
    
    ///////////////////////////////////
    
    #pragma region base

        ///////////////////////////////////    
        
        Collection* newCollection(int numSrchKeys)
        {
            // validation for the numKeys value
            if (numSrchKeys < 0)
                return NULL; // guard

            // memory allocation
            Collection* collection = (Collection*) malloc (sizeof(Collection));
            // initial size shall be 0
            collection->__collection->size = 0;
            // initial limit
            collection->__collection->limit = __LIM_INI; 
            // number of search keys
            *(int *)&collection->__collection->numSrchKeys = numSrchKeys;
            // initial size of the itens[] accordingly to the limit
            collection->__collection->itens = (__Item*) malloc(
                    sizeof(__Item) * collection->__collection->limit
                );
            // initialization of the itens
            //
            return collection;
        }

        Collection* dstrCollection (Collection* collection)
        {
            // contents
            for (int i = 0; i < collection->__collection->size; i++)
                free(collection->__collection->itens->content);
            
            // itens arr
            free(collection->__collection->itens);

            // collection
            free(collection);
            
            return NULL;
        }
        
        ///////////////////////////////////

    #pragma endregion

    ///////////////////////////////////
    
#pragma endregion

///////////////////////////////////