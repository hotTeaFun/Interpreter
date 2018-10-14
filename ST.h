/***************************************************************************
Environment Module
***************************************************************************/
/*=========================================================================
DECLARATIONS
=========================================================================*/
/*-------------------------------------------------------------------------
SYMBOL TABLE RECORD
-------------------------------------------------------------------------*/
#define INIT_LENGTH 4 //初始时分配给各类型变量的数组长度 
typedef emum Bool {false=0,true=1} bool;
typedef enum _flag_for_literal{
    _int=0,_double,_bool,_string,_regexp
} literal_type ;
typedef enum _value_type{
    notexist=0, base, array, fucntion, object,
} value_type ;
typedef struct _literal
{
    literal_type flag;  
    char *string_value; //直接量
} literal;
literal* newliteral() // Allicate space for the literalsc  
{
    return ( literal *) malloc(sizeof(literal));
}
deleteliteral(literal* unused_literal) // free the space of the literals
{
    free(unused_literal);
}
typedef struct _base_value{
    literal value;
    char* id;
} base_value ;
typedef struct _base_values{
    base_value* base_element;
    int length;
} base_values ; 
typedef struct _array_value{
    struct _array_value* array_element;
    int array_length;
    char* id;
    int (*some)();
    int (*every)();
} array_value ;
typedef struct _array_values{
    array_value* array_element;
    int length;
    int allocated_length;
} array_values;
typedef struct _function_value{
    literal** value;
    char* id;
} function_value ;
typedef struct _fucntion_values{
    function_value* function_element;
    int length;
    int allocated_length;
} function_values;
typedef struct _object_value{
    literal** value;
    char* id;
} object_value ;
typedef struct _object_values{
    object_value* object_element;
    int length;
    int allocated_length;
} object_values;
typedef struct _Env {
    base_values     base;
    array_values    array;
    function_values function;
    object_values   object;
    struct _Env*    prev_Env;
} Env;
value_type  test_in_current_env( const Env* env,const char* test_id ){
    value_type revalue = notexist ;
    for(int i=0;i<env->base.length;i++)
        if(strcmp(env->base.base_element[i].id,test_id)){
            revalue=base; return revalue;
            }
    for(int i=0;i<env->array.length;i++)
        if(strcmp(env->array.array_element[i].id,test_id)){
            revalue=array; return revalue;
            }
    for(int i=0;i<env->function.length;i++)
        if(strcmp(env->function.function_element[i].id,test_id)){
            revalue=fucntion; return revalue;
            }
    for(int i=0;i<env->object.length;i++)
        if(strcmp(env->object.object_element[i].id,test_id)){
            revalue=object; return revalue;
            }
    return revalue;
}
value_type test_in_all_env( const Env* env,const char* test_id ){
    for(value_type revalue = notexist; env != NULL; env = env->prev_Env)
    {
        revalue = test_in_current_env(env,test_id);
        if( revalue != notexist ) return revalue;
    }
    return notexist;
} 
base_value  find_base( const Env* env,const char* base_id ){
    for(int i=0;i<env->base.length;i++)
        if(strcmp(env->base.base_element[i].id,base_id))
            return env->base.base_element[i];
    error_report("cannot find base value %s\n",base_id);
    return env->base.base_element[0];
}
array_value  find_array( const Env* env,const char* array_id ){
    for(int i=0;i<env->array.length;i++)
        if(strcmp(env->array.array_element[i].id,array_id))
            return env->array.array_element[i];
    error_report("cannot find array value %s\n",array_id);
    return env->array.array_element[0];        
}
function_value  find_function( const Env* env,const char* function_id ){
    for(int i=0;i<env->function.length;i++)
        if(strcmp(env->function.function_element[i].id,function_id))
            return env->function.function_element[i];
    error_report("cannot find function value %s\n",function_id);
    return env->function.function_element[0];        
}
object_value  find_object( const Env* env,const char* object_id ){
    for(int i=0;i<env->object.length;i++)
        if(strcmp(env->object.object_element[i].id,object_id))
            return env->object.object_element[i];
    error_report("cannot find object value %s\n",object_id);
    return env->object.object_element[0];        
}
bool add_base(Env* env,literal_type type, const char* base_id,const char* value){
    if(test_in_current_env(env,base_id) == notexist){
        if(++env->base.length > env->base.allocated_length){
            env->base.allocated_length *= 2;
            base_value* new_location = (base_value *)realloc(env->base.allocated_length * sizeof(base_value));
            for(int j=0;j<env->base.length-1;j++){
                new_location[j].id = strdup(env->base.base_element[i].id);
                free(env->base.base_element[i].id);
                new_location[j].value.flag = env->base.base_element[i].value.flag;
                new_location[j].value.string_value = strdup(env->base.base_element[i].value.string_value);
                free(env->base.base_element[i].value.string_value);
            }
            new_location[env->base.length-1].id = strdup(base_id);
            new_location[env->base.length-1].value.flag = type;
            new_location[env->base.length-1].value.string_value = strdup(value);
            env->base.base_element = new_location;
        }
        else{
            env->base.base_element[env->base.length-1].id = strdup(base_id);
            env->base.base_element[env->base.length-1].value.flag = type;
            env->base.base_element[env->base.length-1].value.string_value = strdup(value);
        }
        return true;
    }
    else return fasle;
}
Env* init_new_Env(){
    Env* init_Env = (Env *)realloc(sizeof(Env));
    init_Env->base.length     = 0;
    init_Env->array.length    = 0;
    init_Env->function.length = 0;
    init_Env->object.length   = 0;
    init_Env->base.allocted_length      = INIT_LENGTH;
    init_Env->array.allocated_length    = INIT_LENGTH;
    init_Env->function.allocated_length = INIT_LENGTH;
    init_Env->object.allocated_length   = INIT_LENGTH;
    init_Env->base.base_element = (base_value *)realloc(INIT_LENGTH * sizeof(base_value));
    init_Env->array.array_element = (array_value *)realloc(INIT_LENGTH * sizeof(array_value));
    init_Env->function.function_element = (funciton_value *)realloc(INIT_LENGTH * sizeof(function_value));
    init_Env->object,.object_element = (object_value *)realloc(INIT_LENGTH * signed(object_value));
    return init_Env;
}
Env* current_Env = init_new_Env();
Env* step_into_Env(){
    Env* new_Env = init_new_Env();
    new_Env->prev_Env = current_Env;
    current_Env = new_Env;
    return new_Env;
}
Env* step_out_Env(){
    Env* to_delete_Env = current_Env;
    current_Env = current_Env->prev_Env;
    delete_Env(to_delete_Env);
}
delete_Env(Env* to_delete_Env){
    if(to_delete_Env->prev_Env == NULL)
    error_report("cannot delete global Env !");
    else {
        free(to_delete_Env->base.base_element);
        free(to_delete_Env->array.array_element);
        free(to_delete_Env->function.function_element);
        free(to_delete_Env->object,.object_element);
        free(to_delete_Env);
    }
}
error_report(char * error){
    printf("an error occurs: %s\n",error);
}
struct symrec
{
char *name;           /* name of symbol  */
int offset;           /* data offset     */
struct symrec *next;  /* link field      */
};
typedef struct symrec symrec;
/*-------------------------------------------------------------------------
SYMBOL TABLE ENTRY
-------------------------------------------------------------------------*/
symrec *identifier;
/*-------------------------------------------------------------------------
SYMBOL TABLE
Implementation: a chain of records.
------------------------------------------------------------------------*/
symrec *sym_table = (symrec *)0; /* The pointer to the Symbol Table */
/*========================================================================
Operations: Putsym, Getsym
========================================================================*/
symrec * putsym (char *sym_name)
{
symrec *ptr;
ptr = (symrec *) malloc (sizeof(symrec));
ptr->name = (char *) malloc (strlen(sym_name)+1);
strcpy (ptr->name,sym_name);
ptr->offset = data_location();
ptr->next = (struct symrec *)sym_table;
sym_table = ptr;
return ptr;
}
symrec * getsym (char *sym_name)
{
symrec *ptr;
for ( ptr = sym_table;
ptr != (symrec *) 0;
ptr = (symrec *)ptr->next )
if (strcmp (ptr->name,sym_name) == 0)
return ptr;
return 0;
}
/************************** End Symbol Table **************************/
