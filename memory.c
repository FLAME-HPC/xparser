#include "header.h"

void free_modeldata(model_data * modeldata)
{
	freexmachines(modeldata->p_xmachines);
	freexmessages(modeldata->p_xmessages);
	freeenvfunc(modeldata->p_envfuncs);
	freevariables(modeldata->p_envvars);
	freevariables(modeldata->p_envdefines);
	freevariables(modeldata->p_allvars);
	freelayers(modeldata->p_layers);
	freedatatypes(modeldata->p_datatypes);
	free_flame_communications(modeldata->p_communications);
	free_time_units(modeldata->p_time_units);
	free_input_files(modeldata->p_files);
	free(modeldata->name);
	free(modeldata);
}

input_file * add_input_file(input_file ** p_files)
{
	input_file * current, * tmp = NULL;
	current = *p_files;
	
	while(current)
	{
		tmp = current;
		current = current->next;
	}
	/* And current is the new element */
	current = (input_file *)malloc(sizeof(input_file));
	/* Make tmp->next point to current if tmp exists */
	if(tmp) tmp->next = current;
	else
	{
		*p_files = current;
	}
	/* Make current->next point to NULL */
	current->next = NULL;
	current->file = NULL;
	current->fullfilepath = NULL;
	current->fulldirectory = NULL;
	current->localdirectory = NULL;
	current->enabled = 1;
	
	/* Return new element */
	return current;
}

void free_input_files(input_file ** p_files)
{
	input_file * temp, * head;
	head = *p_files;
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		free(head->file);
		free(head->fullfilepath);
		free(head->fulldirectory);
		free(head->localdirectory);
		free(head);
		head = temp;
	}
	
	*p_files = NULL;
}

xmachine_ioput * addioput(xmachine_ioput ** p_ioput)
{
	xmachine_ioput * current, * tmp = NULL;
	current = *p_ioput;
	
	while(current)
	{
		tmp = current;
		current = current->next;
	}
	/* And current is the new element */
	current = (xmachine_ioput *)malloc(sizeof(xmachine_ioput));
	/* Make tmp->next point to current if tmp exists */
	if(tmp) tmp->next = current;
	else
	{
		*p_ioput = current;
	}
	/* Make current->next point to NULL */
	current->next = NULL;
	current->filter_function = NULL;
	current->filter_rule = NULL;
	
	/* Return new element */
	return current;
}

void free_ioput(xmachine_ioput ** p_ioput)
{
	xmachine_ioput * temp, * head;
	head = *p_ioput;
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		free(head->filter_function);
		free_rule_data(&head->filter_rule);
		free(head->messagetype);
		free(head);
		head = temp;
	}
	
	*p_ioput = NULL;
}

/** \fn f_code * addfcode(f_code ** p_code)
 * \brief Allocate memory for a linked list of datatype code.
 * \param p_code Pointer Pointer to the code list.
 * \return Pointer to the added code.
 */
f_code * addfcode(f_code ** p_code)
{
	f_code * current, * tmp = NULL;
	current = *p_code;
	
	while(current)
	{
		tmp = current;
		current = current->next;
	}
	/* And current is the new element */
	current = (f_code *)malloc(sizeof(f_code));
	/* Make tmp->next point to current if tmp exists */
	if(tmp) tmp->next = current;
	else
	{
		*p_code = current;
	}
	/* Make current->next point to NULL */
	current->code = NULL;
	current->next = NULL;
	
	/* Return new element */
	return current;
}

/** \fn void freefcode(f_code ** p_code)
 * \brief Free memory from a linked list of code.
 * \param p_code Pointer Pointer to the code list.
 */
void freefcode(f_code ** p_code)
{
	f_code * temp, * head;
	head = *p_code;
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		/* Free the cell memory */
		/*freechars(&head->code);*/
		free(head);
		head = temp;
	}
	
	*p_code = NULL;
}

/** \fn variable * addvariable(variable ** p_vars)
 * \brief Allocate memory for a linked list of datatype variable.
 * \param p_vars Pointer Pointer to the variables list.
 * \return Pointer to the added variable.
 */
variable * addvariable(variable ** p_vars)
{
	variable * current, * tmp = NULL;
	current = *p_vars;
	
	while(current)
	{
		tmp = current;
		current = current->next;
	}
	/* And current is the new element */
	current = (variable *)malloc(sizeof(variable));
	/* Make tmp->next point to current if tmp exists */
	if(tmp) tmp->next = current;
	else
	{
		*p_vars = current;
	}
	/* Make current->next point to NULL */
	current->type = NULL;
	current->name = NULL;
	current->value = NULL;
	current->datatype = NULL;
	current->file = NULL;
	current->next = NULL;
	current->typenotarray = NULL;
	
	/* Return new element */
	return current;
}

/** \fn void freevariables(variable ** p_vars)
 * \brief Free memory for a linked list of datatype variable.
 * \param p_vars Pointer Pointer to the variables list.
 */
void freevariables(variable ** p_vars)
{
	variable * temp, * head;
	head = *p_vars;
	
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		/* Free the cell memory */
		/*freechars(&head->name);*/
		/*freechars(&head->type);*/
		/*freechars(&head->value);*/
		free(head->type);
		free(head->name);
		free(head->value);
		free(head->typenotarray);
		free(head->file);
		free(head);
		head = temp;
	}
	
	*p_vars = NULL;
}

/** \fn xmachine_memory * addxmemory(xmachine_memory ** p_xmemory)
 * \brief Allocate memory for a linked list of datatype xmachine.
 * \param p_xmemory Pointer Pointer to the xmachines list.
 * \return Pointer to the added xmachine.
 */
xmachine_memory * addxmemory(xmachine_memory ** p_xmemory)
{
	xmachine_memory * current, * temp = NULL;
	current = *p_xmemory;
	
	if(p_xmemory != NULL)
	{
		while(current)
		{
			temp = current;
			current = current->next;
		}
	}
	/* And current is the new element */
	if((current = (xmachine_memory *)malloc(sizeof(xmachine_memory))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}
	/* Make tmp->next point to current if tmp exists */
	if(temp) temp->next = current;
	else
	{
		*p_xmemory = current;
	}
	/* Make current->next point to NULL */
	current->vars = NULL;
	current->next = NULL;

	/* Return new element */
	return current;
}

/** \fn void freexmemory(xmachine_memory ** p_xmemory)
 * \brief Free memory for a linked list of datatype xmachine.
 * \param p_xmemory Pointer Pointer to the xmachines list.
 */
void freexmemory(xmachine_memory ** p_xmemory)
{
	xmachine_memory * temp, * head;
	head = *p_xmemory;
	
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		/* Free the cell memory */
		freevariables(&head->vars);
		free(head);
		head = temp;
	}
	
	*p_xmemory = NULL;
}

/** \fn env_func * addenvfunc(env_func ** p_env_funcs)
 * \brief Allocate memory for a linked list of datatype environment functions.
 * \param p_env_funcs Pointer Pointer to the environment functions list.
 * \return Pointer to the added environment function.
 */
env_func * addenvfunc(env_func ** p_env_funcs)
{
	env_func * current, * temp = NULL;
	current = *p_env_funcs;
	
	while(current)
	{
		temp = current;
		current = current->next;
	}
	/* And current is the new element */
	if((current = (env_func *)malloc(sizeof(env_func))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}
	/* Make tmp->next point to current if tmp exists */
	if(temp) temp->next = current;
	else
	{
		*p_env_funcs = current;
	}
	/* Make current->next point to NULL */
	current->code = NULL;
	current->filepath = NULL;
	current->next = NULL;

	/* Return new element */
	return current;
}

/** \fn void freeenvfunc(env_func ** p_env_funcs)
 * \brief Free memory for a linked list of datatype environment function.
 * \param p_env_funcs Pointer Pointer to the environment functions list.
 */
void freeenvfunc(env_func ** p_env_funcs)
{
	env_func * temp, * head;
	head = *p_env_funcs;
	
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		/* Free the cell memory */
		/*freechars(&head->code);*/
		free(head->filepath);
		free(head);
		head = temp;
	}
	
	*p_env_funcs = NULL;
}

/** \fn xmachine_message * addxmessage(xmachine_message ** p_xmessage)
 * \brief Allocate memory for a linked list of datatype message.
 * \param p_xmessage Pointer Pointer to the messages list.
 * \return Pointer to the added message.
 */
xmachine_message * addxmessage(xmachine_message ** p_xmessage)
{
	xmachine_message * current, * temp = NULL;
	current = *p_xmessage;
	
	while(current)
	{
		temp = current;
		current = current->next;
	}
	/* And current is the new element */
	if((current = (xmachine_message *)malloc(sizeof(xmachine_message))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}
	/* Make tmp->next point to current if tmp exists */
	if(temp) temp->next = current;
	else
	{
		*p_xmessage = current;
	}
	/* Make current->next point to NULL */
	current->name = NULL;
	current->vars = NULL;
	current->functions = NULL;
	current->next = NULL;
	current->first = 0;
	current->last = 0;
	current->file = NULL;

	/* Return new element */
	return current;
}

/** \fn void freexmessages(xmachine_message ** p_xmessage)
 * \brief Free memory for a linked list of datatype message.
 * \param p_xmessage Pointer Pointer to the messages list.
 */
void freexmessages(xmachine_message ** p_xmessage)
{
	xmachine_message * temp, * head;
	head = *p_xmessage;
	
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		/* Free the cell memory */
		free(head->name);
		freevariables(&head->vars);
		freeenvfunc(&head->functions);
		free(head->file);
		free(head);
		head = temp;
	}
	
	*p_xmessage = NULL;
}

void addstateholder(xmachine_state * state, xmachine_state_holder ** p_list)
{
	xmachine_state_holder * current;
	
	if((current = (xmachine_state_holder *)malloc(sizeof(xmachine_state_holder))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}
	
	current->state = state;
	current->next = *p_list;
	*p_list = current;
}

void freestateholder(xmachine_state_holder ** p_list)
{
	xmachine_state_holder * temp, * head;
	head = *p_list;
	
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
	
	*p_list = NULL;
}

/** \fn xmachine_state * addxstate(xmachine_state ** p_xstates)
 * \brief Allocate memory for a linked list of datatype state.
 * \param p_xstates Pointer Pointer to the states list.
 * \return Pointer to the added state.
 */
void addxstate(char * name, xmachine_state ** p_xstates)
{
	xmachine_state * current, * temp;
	current = *p_xstates;
	temp = *p_xstates;
	int flag = 0;
	
	while(current && flag == 0)
	{
		if(strcmp(current->name, name) == 0) flag = 1;
		
		current = current->next;
	}
	
	if(flag == 0)
	{
		/* And current is the new element */
		if((current = (xmachine_state *)malloc(sizeof(xmachine_state))) == NULL)
		{
			printf("Error: Cannot allocate memory\n");
			exit(0);
		}
		/* Make tmp->next point to current if tmp exists */
		current->next = temp;
		*p_xstates = current;
		
		/* Make current->next point to NULL */
		current->name = copystr(name);
	}
}

/** \fn void freexstates(xmachine_state ** p_xstates)
 * \brief Free memory for a linked list of datatype state.
 * \param p_xstates Pointer Pointer to the states list.
 */
void freexstates(xmachine_state ** p_xstates)
{
	xmachine_state * temp, * head;
	head = *p_xstates;
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		/* Free the cell memory */
		free(head->name);
		free(head);
		head = temp;
	}
	
	*p_xstates = NULL;
}

void add_flame_communication(char * messagetype, xmachine_function * function1, xmachine_function * function2, flame_communication ** communications)
{
	flame_communication * current, * tmp = * communications;
	
	/* And current is the new element */
	current = (flame_communication *)malloc(sizeof(flame_communication));
	/* Make tmp->next point to current if tmp exists */
	current->next = tmp;
	* communications = current;
	
	current->input_function = function1;
	current->output_function = function2;
	
	current->messagetype = copystr(messagetype);
}

void free_flame_communications(flame_communication ** communications)
{
	flame_communication * temp, * head;
	head = * communications;
	
	while(head)
	{
		temp = head->next;
		free(head->messagetype);
		free(head);
		
		head = temp;
	}
	
	* communications = NULL;
}

void add_time_unit(char * name, char * unit_name, int period, time_data ** p_time_units)
{
	time_data * current, * temp = NULL;
	
	current = *p_time_units;
	while(current)
	{
		temp = current;
		current = current->next;
	}
	/* And current is the new element */
	if((current = (time_data *)malloc(sizeof(time_data))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}
	/* Make tmp->next point to current if tmp exists */
	if(temp) temp->next = current;
	else
	{
		*p_time_units = current;
	}
	
	current->name = copystr(name);
	current->unit = NULL;
	current->period = period;
	current->next = NULL;
	current->iterations = 0;
	
	/*printf("time: name: %s unit: %s period: %d\n", name, unit_name, period);*/
	
	/* Find unit name struct */
	if(strcmp(unit_name, "ITERATION") == 0 || strcmp(unit_name, "iteration") == 0) current->iterations = 1;
	else
	{
		temp = * p_time_units;
		while(temp)
		{
			if(strcmp(unit_name, temp->name) == 0)
			{
				current->unit = temp;
				current->iterations = temp->iterations * current->period;
			}
			
			temp = temp->next;
		}
		if(current->unit == NULL)
		{
			printf("ERROR: time unit '%s' not found in time name '%s'\n", unit_name, name);
			exit(0); // todo
		}
	}
}

void free_time_units(time_data ** p_time_units)
{
	time_data * temp, * head;
	head = * p_time_units;
	
	while(head)
	{
		temp = head->next;
		free(head->name);
		free(head);
		
		head = temp;
	}
	
	* p_time_units = NULL;
}

/** \fn char * copystr(char * string)
 * \brief Copy a string into new memory.
 * \param string The string to copy.
 * \return The copy of the string.
 */
char * copystr(char * string)
{
	char * new_string = (char *)malloc( (strlen(string) + 1) * sizeof(char));
	strcpy(new_string, string);
	return new_string;
}

adj_function * add_depends_adj_function(xmachine_function * current_function)
{
	adj_function * current;
	
	current = (adj_function *)malloc(sizeof(adj_function));
	current->next = current_function->depends;
	current_function->depends = current;
	
	current->function = NULL;
	current->name = NULL;
	current->type = NULL;
	
	return current;
}

void add_adj_function_simple(xmachine_function * function1, xmachine_function * function2)
{
	adj_function * current;
	
	current = (adj_function *)malloc(sizeof(adj_function));
	current->function = function2;
	current->next = function1->alldepends;
	function1->alldepends = current;
	current->name = NULL;
	current->type = NULL;
}

void remove_adj_function_simple(xmachine_function * function1)
{
	adj_function * current;
	
	if(function1->alldepends != NULL)
	{
		current = function1->alldepends->next;
		free(function1->alldepends);
		function1->alldepends = current;
	}
}

void add_adj_function_recent(xmachine_function * function1, xmachine_function * function2)
{
	adj_function * current;
	
	current = (adj_function *)malloc(sizeof(adj_function));
	current->function = function2;
	current->next = function1->recentdepends;
	function1->recentdepends = current;
	current->name = NULL;
	current->type = NULL;
}

void remove_adj_function_recent(xmachine_function * function1)
{
	adj_function * current;
	
	if(function1->recentdepends != NULL)
	{
		current = function1->recentdepends->next;
		free(function1->recentdepends->name);
		free(function1->recentdepends->type);
		free(function1->recentdepends);
		function1->recentdepends = current;
	}
}

void add_adj_function(xmachine_function * function1, xmachine_function * function2, char * type)
{
	adj_function * current;
	
	current = (adj_function *)malloc(sizeof(adj_function));
	current->function = function1;
	current->type = copystr(type);
	current->next = function2->dependson;
	current->name = NULL;
	function2->dependson = current;
	
	current = (adj_function *)malloc(sizeof(adj_function));
	current->function = function2;
	current->type = copystr(type);
	current->next = function1->dependants;
	current->name = NULL;
	function1->dependants = current;
}

void free_adj_function(adj_function * adj_functions)
{
	adj_function * temp, * head;
	head = adj_functions;
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		
		free(head->type);
		free(head->name);
		
		free(head);
		head = temp;
	}
}

rule_data * add_rule_data(rule_data ** p_data)
{
	rule_data * current, * temp = NULL;
	current = *p_data;
	
	while(current)
	{
		temp = current;
		current = current->next;
	}
	/* And current is the new element */
	if((current = (rule_data *)malloc(sizeof(rule_data))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}
	/* Make tmp->next point to current if tmp exists */
	if(temp) temp->next = current;
	else
	{
		*p_data = current;
	}
	/* Make current->next point to NULL */
	current->lhs = NULL;
	current->rhs = NULL;
	current->op = NULL;
	current->lhs_rule = NULL;
	current->rhs_rule = NULL;
	current->next = NULL;
	current->time_rule = 0;
	current->not = 0;
	current->has_agent_var = 0;
	current->has_message_var = 0;

	/* Return new element */
	return current;
}

void free_rule_data(rule_data ** p_data)
{
	rule_data * temp, * head;
	head = *p_data;
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		
		free(head->lhs);
		free(head->rhs);
		free(head->op);
		free_rule_data(&head->lhs_rule);
		free_rule_data(&head->rhs_rule);
		free(head);
		head = temp;
	}
	
	*p_data = NULL;
}

/** \fn xmachine_function * addxfunction(xmachine_function ** p_xfunctions)
 * \brief Allocate memory for a linked list of datatype function.
 * \param p_xfunctions Pointer Pointer to the functions list.
 * \return Pointer to the added function.
 */
xmachine_function * addxfunction(xmachine_function ** p_xfunctions)
{
	xmachine_function * current, * temp = NULL;
	current = *p_xfunctions;
	
	while(current)
	{
		temp = current;
		current = current->next;
	}
	/* And current is the new element */
	if((current = (xmachine_function *)malloc(sizeof(xmachine_function))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}
	/* Make tmp->next point to current if tmp exists */
	if(temp) temp->next = current;
	else
	{
		*p_xfunctions = current;
	}
	/* Make current->next point to NULL */
	current->name = NULL;
	current->note = NULL;
	current->file = NULL;
	current->code = NULL;
	current->inputs = NULL;
	current->outputs = NULL;
	current->current_state = NULL;
	current->next_state = NULL;
	current->first_inputs = NULL;
	current->last_outputs = NULL;
	current->dependson = NULL;
	current->dependants = NULL;
	current->alldepends = NULL;
	current->depends = NULL;
	current->recentdepends = NULL;
	current->agent_name = NULL;
	current->next = NULL;
	current->x = 0.0;
	current->y = 0.0;
	current->rank_in = -1;
	current->rank_out = -1;
	current->condition_rule = NULL;
	current->condition_function = NULL;

	/* Return new element */
	return current;
}

/** \fn void freexfunctions(xmachine_function ** p_xfunctions)
 * \brief Free memory for a linked list of datatype function.
 * \param p_xfunctions Pointer Pointer to the functions list.
 */
void freexfunctions(xmachine_function ** p_xfunctions)
{
	xmachine_function * temp, * head;
	head = *p_xfunctions;
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		/* Free the cell memory */
		free(head->name);
		free(head->note);
		free(head->file);
		free(head->current_state);
		free(head->next_state);
		free(head->agent_name);
		free(head->condition_function);
		freefcode(&head->code);
		free_ioput(&head->inputs);
		free_ioput(&head->outputs);
		free_ioput(&head->first_inputs);
		free_ioput(&head->last_outputs);
		free_adj_function(head->dependson);
		free_adj_function(head->dependants);
		free_adj_function(head->alldepends);
		free_adj_function(head->depends);
		free_adj_function(head->recentdepends);
		free_rule_data(&head->condition_rule);
		free(head);
		head = temp;
	}
	
	*p_xfunctions = NULL;
}

/** \fn xmachine * addxmachine(xmachine ** p_xmachines)
 * \brief Allocate memory for a linked list of datatype xmachine.
 * \param p_xmachines Pointer Pointer to the xmachines list.
 * \return Pointer to the added xmachine.
 */
xmachine * addxmachine(xmachine ** p_xmachines, char * name)
{
	int number = 0;
	xmachine * current = *p_xmachines;
	xmachine * temp = NULL;
	
	while(current)
	{
		/* If agent name already exists */
		if(strcmp(current->name, name) == 0) return current;
		
		temp = current;
		current = current->next;
		number++;
	}
	/* And current is the new element */
	if((current = (xmachine *)malloc(sizeof(xmachine))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}
	/* Make tmp->next point to current if tmp exists */
	if(temp) temp->next = current;
	else
	{
		*p_xmachines = current;
	}
	/* Make current->next point to NULL */
	current->number = number;
	current->name = copystr(name);
	current->memory = NULL;
	addxmemory(&current->memory);
	current->states = NULL;
	current->functions = NULL;
	
	current->start_state = NULL;
	current->end_states = NULL;
	
	current->idvar[0] = 0;
	current->xvar[0] = 0;
	current->yvar[0] = 0;
	current->zvar[0] = 0;

	current->rangevar[0] = 0;
	current->idvar[0] = 0;

	current->next = NULL;

	/* Return new element */
	return current;
}

/** \fn void freexmachines(xmachine ** p_xmachines)
 * \brief Free memory for a linked list of datatype xmachine.
 * \param p_xmachines Pointer Pointer to the xmachines list.
 */
void freexmachines(xmachine ** p_xmachines)
{
	xmachine * temp, * head;
	head = *p_xmachines;
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		/* Free the cell memory */
		free(head->name);
		freexmemory(&head->memory);
		freexstates(&head->states);
		freexfunctions(&head->functions);
		freestateholder(&head->end_states);
		free(head);
		head = temp;
	}
	
	*p_xmachines = NULL;
}

/** \fn layer * addlayer(communication_layer * com_layer)
 * \brief Allocate memory for a linked list of datatype layer.
 * \param com_layer Pointer Pointer to the layers list.
 * \return Pointer to the added layer.
 */
layer * addlayer(layer ** p_layer)
{
	layer * current, * temp;
	
	/* And current is the new element */
	if((current = (layer *)malloc(sizeof(layer))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}
	current->functions = NULL;
	
	temp = * p_layer;
	if(temp == NULL)
	{
		current->next = * p_layer;
		current->number = 0;
		*p_layer = current;
	}
	else
	{
		while(temp->next)
		{
			temp = temp->next;
		}
		temp->next = current;
		current->next = NULL;
		current->number = temp->number + 1;
	}
	
	/* Return new element */
	return current;
}

/** \fn void freelayers(layer * layers)
 * \brief Free memory for a linked list of datatype layer.
 * \param layers Pointer to the layers list.
 */
void freelayers(layer ** p_layers)
{
	layer * temp, * head;
	head = * p_layers;
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		/* Free the cell memory */
		freefunction_pointers(&head->functions);
		free(head);
		head = temp;
	}
	
	* p_layers = NULL;
}

/** \fn communication_layer * addcommunication_layer(communication_layer ** p_com_layers)
 * \brief Allocate memory for a linked list of datatype layer.
 * \param p_com_layers Pointer Pointer to the layers list.
 * \return Pointer to the added layer.
 */
void addfunction_pointer(function_pointer ** p_function_pointers, xmachine_function * function)
{
	function_pointer * current;
	
	/* And current is the new element */
	if((current = (function_pointer *)malloc(sizeof(function_pointer))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}
	/* Make current->next point to NULL */
	current->function = function;
	current->next = *p_function_pointers;
	*p_function_pointers = current;
}

/** \fn void freefunction_pointers(function_pointer ** p_function_pointers)
 * \brief Free memory for a linked list of datatype layer.
 * \param p_com_layers Pointer Pointer to the layers list.
 */
void freefunction_pointers(function_pointer ** p_function_pointers)
{
	function_pointer * temp, * head;
	head = *p_function_pointers;
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
	
	*p_function_pointers = NULL;
}

/** \fn layer * adddatatype(model_datatype ** p_datatypes)
 * \brief Allocate memory for a linked list of datatype layer.
 * \param p_datatypes Pointer Pointer to the datatypes list.
 * \return Pointer to the added datatype.
 */
model_datatype * adddatatype(model_datatype ** p_datatypes)
{
	model_datatype * current, * head, * temp;
	head = * p_datatypes;
	temp = head;
	
	/* And current is the new element */
	if((current = (model_datatype *)malloc(sizeof(model_datatype))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}
	current->vars = NULL;
	current->next = NULL;
	current->desc = NULL;
	current->name = NULL;
	/* Find end of list */
	if(* p_datatypes == NULL)
	{
		* p_datatypes = current;
	}
	else
	{
		while(head)
		{
			temp = head;
			head = temp->next;
		}
		temp->next = current;
	}
	
	/* Return new element */
	return current;
}

/** \fn void freedatatypes(model_datatype ** p_datatypes)
 * \brief Free memory for a linked list of datatype layer.
 * \param p_datatypes Pointer Pointer to the datatype list.
 */
void freedatatypes(model_datatype ** p_datatypes)
{
	model_datatype * temp, * head;
	head = * p_datatypes;
	/* Loop until new elements of cells left */
	while(head)
	{
		temp = head->next;
		/* Free the cell memory */
		freevariables(&head->vars);
		free(head->name);
		free(head->desc);
		free(head);
		head = temp;
	}
	
	* p_datatypes = NULL;
}

/** \fn int_array * init_int_array()
 * \brief Allocate memory for a dynamic integer array.
 * \return int_array Pointer to the new dynamic integer array.
 */
int_array * init_int_array(void)
{
	int_array * new_array = (int_array *)malloc(sizeof(int_array));
	new_array->size = 0;
	new_array->total_size = ARRAY_BLOCK_SIZE;
	new_array->array = (int *)malloc(ARRAY_BLOCK_SIZE * sizeof(int));
	
	return new_array;
}

/** \fn void free_int_array(int_array * array)
 * \brief Free the memory of a dynamic integer array.
 * \param array Pointer to the dynamic integer array.
 */
void free_int_array(int_array * array)
{
	free(array->array);
	free(array);
}

/** \fn void sort_int_array(int_array * array)
 * \brief Sort the elements of a dynamic integer array with smallest first.
 * \param array Pointer to the dynamic integer array.
 */
void sort_int_array(int_array * array)
{
	int i, j, temp;
	
	/* Using bubble sorts nested loops */
	for(i=0; i<(array->size-1); i++)
	{
		for(j=0; j<(array->size-1)-i; j++) 
		{
			/* Comparing the values between neighbours */
			if(*(array->array+j+1) < *(array->array+j))
			{
				/* Swap neighbours */
				temp = *(array->array+j); 
				*(array->array+j) = *(array->array+j+1);
				*(array->array+j+1) = temp;
			}
		}
	}
}

/** \fn int quicksort_int(int *array, int elements)
 *  \brief Sorts the elements of the integer array in ascending order.
 *  \param Pointer to integer array
 *  \param Number of elements that must be sorted
 *  \return integer value indicating success(0) or failure(1)
 */
int quicksort_int(int * array, int elements)
{
	#define  LEVEL  1000
	int  pivot, begin[LEVEL], end[LEVEL], i=0, left, right ;
	begin[0]=0; end[0]=elements;
	while (i>=0)
	{
		left=begin[i]; right=end[i]-1;
		if (left<right)
		{
			pivot=array[left]; if (i==LEVEL-1) return 1;
			while (left<right)
			{
				while (array[right]>=pivot && left<right) right--;
				if (left<right) array[left++]=array[right];
				while (array[left]<=pivot && left<right) left++;
				if (left<right) array[right--]=array[left];
			}
			array[left]=pivot;
			begin[i+1]=left+1;
			end[i+1]=end[i];
			end[i++]=left;
		}
	    else 
	    {
	      i--;
	    }
	}
	return 0;
}

/** \fn void add_int(int_array * array, int new_int)
 * \brief Add an integer to the dynamic integer array.
 * \param array Pointer to the dynamic integer array.
 * \param new_int The integer to add
 */
void add_int(int_array * array, int new_int)
{
	if(array->size == array->total_size)
	{
		array->total_size = array->total_size + ARRAY_BLOCK_SIZE;
		array->array = (int *)realloc(array->array, (array->total_size * sizeof(int)));
	}
	
	array->array[array->size] = new_int;
	array->size++;
}

/** \fn void remove_int(int_array * array, int index)
 * \brief Remove an integer from a dynamic integer array.
 * \param array Pointer to the dynamic integer array.
 * \param index The index of the integer to remove.
 */
void remove_int(int_array * array, int index)
{
	int i;
	
	if(index <= array->size)
	{
		/* memcopy??*/
		for(i = index; i < array->size; i++)
		{
			array->array[i] = array->array[i+1];
		}
		
		array->size--;
	}
}

/** \fn void print_int_array(int_array * array)
 * \brief Print the elements of a dynamic integer array.
 * \param array Pointer to the dynamic integer array.
 */
void print_int_array(int_array * array)
{
	int i;
	printf("\n");
	for(i=0; i<array->size; i++)
	{
		printf("%d> %d\n", i, array->array[i]);
	}
}

/** \fn double_array * init_double_array()
 * \brief Allocate memory for a dynamic double array.
 * \return double_array Pointer to the new dynamic double array.
 */
double_array * init_double_array()
{
	double_array * new_array = (double_array *)malloc(sizeof(double_array));
	new_array->size = 0;
	new_array->total_size = ARRAY_BLOCK_SIZE;
	new_array->array = (double *)malloc(ARRAY_BLOCK_SIZE * sizeof(double));
	
	return new_array;
}

/** \fn void free_double_array(double_array * array)
 * \brief Free the memory of a dynamic double array.
 * \param array Pointer to the dynamic double array.
 */
void free_double_array(double_array * array)
{
	free(array->array);
	free(array);
}

/** \fn void sort_double_array(double_array * array)
 * \brief Sort the elements of a dynamic double array with smallest first.
 * \param array Pointer to the dynamic double array.
 */
void sort_double_array(double_array * array)
{
	int i, j;
	double temp;
	
	/* Using bubble sorts nested loops */
	for(i=0; i<(array->size-1); i++)
	{
		for(j=0; j<(array->size-1)-i; j++) 
		{
			/* Comparing the values between neighbours */
			if(*(array->array+j+1) < *(array->array+j))
			{
				/* Swap neighbours */
				temp = *(array->array+j); 
				*(array->array+j) = *(array->array+j+1);
				*(array->array+j+1) = temp;
			}
		}
	}
}

/** \fn int quicksort_double(double *array, int elements)
 *  \brief Sorts the elements of the double array in ascending order.
 *  \param Pointer to double array
 *  \param Number of elements that must be sorted
 *  \return integer value indicating success(0) or failure(1)
 */
int quicksort_double(double * array, int elements)
{
	#define  LEVEL  1000
	double pivot, begin[LEVEL], end[LEVEL];
	int  i=0, left, right ; 
	begin[0]=0; end[0]=elements;
	while (i>=0)
	{
		left=begin[i]; right=end[i]-1;
		if (left<right)
		{
			pivot=array[left]; if (i==LEVEL-1) return 1;
			while (left<right)
			{
				while (array[right]>=pivot && left<right) right--;
				if (left<right) array[left++]=array[right];
				while (array[left]<=pivot && left<right) left++;
				if (left<right) array[right--]=array[left];
			}
			array[left]=pivot;
			begin[i+1]=left+1;
			end[i+1]=end[i];
			end[i++]=left;
		}
	    else 
	    {
	      i--;
	    }
	}
	return 0;
}

/** \fn void add_double(double_array * array, double new_double)
 * \brief Add an double to the dynamic double array.
 * \param array Pointer to the dynamic double array.
 * \param new_double The double to add
 */
void add_double(double_array * array, double new_double)
{
	if(array->size == array->total_size)
	{
		array->total_size = array->total_size + ARRAY_BLOCK_SIZE;
		array->array = (double *)realloc(array->array, (array->total_size * sizeof(double)));
	}
	
	array->array[array->size] = new_double;
	array->size++;
}

/** \fn void remove_double(double_array * array, int index)
 * \brief Remove an double from a dynamic double array.
 * \param array Pointer to the dynamic double array.
 * \param index The index of the double to remove.
 */
void remove_double(double_array * array, int index)
{
	int i;
	
	if(index <= array->size)
	{
		/* memcopy??*/
		for(i = index; i < array->size; i++)
		{
			array->array[i] = array->array[i+1];
		}
		
		array->size--;
	}
}

/** \fn void print_double_array(double_array * array)
 * \brief Print the elements of a dynamic double array.
 * \param array Pointer to the dynamic double array.
 */
void print_double_array(double_array * array)
{
	int i;
	printf("\n");
	for(i=0; i<array->size; i++)
	{
		printf("%d> %f\n", i, array->array[i]);
	}
}

/** \fn char_array * init_char_array()
 * \brief Allocate memory for a dynamic chareger array.
 * \return char_array Pocharer to the new dynamic chareger array.
 */
char_array * init_char_array()
{
	char_array * new_array = (char_array *)malloc(sizeof(char_array));
	new_array->size = 0;
	new_array->total_size = ARRAY_BLOCK_SIZE;
	new_array->array = (char *)malloc(ARRAY_BLOCK_SIZE * sizeof(char));
	new_array->array[0] = '\0';
	
	return new_array;
}

void reset_char_array(char_array * array)
{
	array->size = 0;
	array->array[0] = '\0';
}

/** \fn void free_char_array(char_array * array)
 * \brief Free the memory of a dynamic chareger array.
 * \param array Pocharer to the dynamic chareger array.
 */
void free_char_array(char_array * array)
{
	free(array->array);
	free(array);
}

/** \fn void add_char(char_array * array, char new_char)
 * \brief Add an chareger to the dynamic chareger array.
 * \param array Pocharer to the dynamic chareger array.
 * \param new_char The chareger to add
 */
void add_char(char_array * array, char new_char)
{
	if(array->size + 1 == array->total_size)
	{
		array->total_size = array->total_size + ARRAY_BLOCK_SIZE;
		array->array = (char *)realloc(array->array, (array->total_size * sizeof(char)));
	}
	
	array->array[array->size] = new_char;
	array->array[array->size + 1] = '\0';
	array->size++;
}

/** \fn char * copy_array_to_str(char_array * array)
 * \brief Return pointer to string from a char_array.
 * \param array Pointer to the dynamic integer array.
 * \return char Pointer to the new string.
 */
char * copy_array_to_str(char_array * array)
{
	char * new_string = (char *)malloc( (array->size + 1) * sizeof(char));
	return strcpy(new_string, array->array);
}

/** \fn void remove_char(char_array * array, int index)
 * \brief Remove an chareger from a dynamic chareger array.
 * \param array Pointer to the dynamic integer array.
 * \param index The index of the chareger to remove.
 */
void remove_char(char_array * array, int index)
{
	int i;
	
	if(index <= array->size)
	{
		/* memcopy??*/
		for(i = index; i < array->size + 1; i++)
		{
			array->array[i] = array->array[i+1];
		}
		
		array->size--;
	}
}

/** \fn void print_char_array(char_array * array)
 * \brief Print the elements of a dynamic chareger array.
 * \param array Pointer to the dynamic chareger array.
 */
void print_char_array(char_array * array)
{
	printf("%s\n", array->array);
}
