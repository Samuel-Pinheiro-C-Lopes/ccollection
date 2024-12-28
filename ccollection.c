///////////////////////////////////

#pragma region DEPENDECIES 

    #include "ccollection.h"

#pragma endregion

///////////////////////////////////

#pragma region ITEM 

    ///////////////////////////////////
    
    #pragma region struct 

        struct __item 
        {
            // logical exclusion
            char active;
            // primary key
            char *pkey;
            // pointer to content of any type
            void *content;
            // array of pointers to the search keys
            void *skeys[];
        };

    #pragma endregion
    
    ///////////////////////////////////

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
            const int numSrchKeys;
            // array of itens
            __Item itens[]; 
        };

    #pragma endregion

    ///////////////////////////////////

#pragma endregion

///////////////////////////////////

#pragma region HEADER

    static __Item newItem(void *const content, char *const pkey, void **const skeys, int length);
    static int addItem(Collection *const collection, __Item item);
    static int reallocCol(Collection *const collection);

#pragma endregion

///////////////////////////////////

#pragma region FUNCTIONS

    ///////////////////////////////////
    
    #pragma region crud
        // if product is a pointer to Product product;
        // addNewItem(collection, product, &product->id, &product->age, &product->name, &product->currency)

        int addNewItem(Collection *const collection, void *const content, char *pkey, ...)
        {
            int result;

            void *skeys[collection->__collection->numSrchKeys];

            // pointers of the search keys provided by the variadic part of arguments
            if (collection->__collection->numSrchKeys > 0)
            {
                va_list vl;
                va_start(vl, pkey);
                int i;

                for (i = 0; i < collection->__collection->numSrchKeys; i++)
                    skeys[i] = va_arg(vl, void*);
                
                // creates an __Item and adds it's content to the __Item array of the collection
                result = addItem(collection, newItem(content, pkey, skeys, i + 1));
            }
            else 
                result = addItem(collection, newItem(content, pkey, skeys, 0));  

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
            collection->__collection->limit *= 2;

            if (reallocCol(collection) == 0)
                return 0;
        }

        // assign the new item to it's location
        collection->__collection->itens[collection->__collection->size] = item;
        collection->__collection->size++;

        // return success
        return 1;
    }

    
    static __Item newItem(void *const content, char *const pkey, void *skeys[], int length)
    {
        // memory allocation
        __Item item = 
        {
            .active = __I_ACTIVE,
            .pkey = pkey,
        };

        for (int i = 0; i < length; i++)
            item.skeys[i] = skeys[i];

        // returns the item
        return item;
    }
    

    static int reallocCol(Collection *const collection)
    {
        __Collection *new_col = realloc(
            collection->__collection, 
            sizeof(__Collection) + 
            (sizeof(__Item*) * collection->__collection->limit) +
            (sizeof(void *) * collection->__collection->limit * collection->__collection->numSrchKeys)
        );
        
        if (new_col == NULL)
            return 0;
        
        collection->__collection = new_col;
        return 1;
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
            // size for the __collection, shall be the __Collection + items + srchKeys of the items
            size_t total_size = 
                (sizeof(__Collection)) +
                (sizeof(__Item) * __LIM_INI) +
                (sizeof(void *) * numSrchKeys * __LIM_INI);
            
            // the private member
            collection->__collection = (__Collection *) malloc(total_size);

            // initial size shall be 0
            collection->__collection->size = 0;
            // initial limit
            collection->__collection->limit = __LIM_INI; 
            // number of search keys
            *(int *)&collection->__collection->numSrchKeys = numSrchKeys;

            // initialization of the itens
            
            return collection;
        }

        Collection* dstrCollection (Collection* collection)
        {
            // contents
            // we don't malloc them, I don't think we should free them neither
            //for (int i = 0; i < collection->__collection->size; i++)
                // free(collection->__collection->itens[i].content);

            free(collection->__collection);
            
            // itens arr
            //free(collection->__collection->itens);

            // collection
            free(collection);
            
            return NULL;
        }
        
        ///////////////////////////////////

    #pragma endregion

    ///////////////////////////////////
    
#pragma endregion

///////////////////////////////////