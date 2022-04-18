#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    bool mark;                                                     //used in mark and sweep mechanism for marking it 1 for alive and 0 for dead.
    int ref_count;                                                 // used in reference count mechanism to check how many nodes point to it.
    struct node *next_1;                                           //maximum three next nodes as shown in fig.
    struct node *next_2;
    struct node *next_3;
                                        
    
}Node;

 Node *pointer_array[8];                                      // 8 globally pointer nodes named as 1,2,3,5,7,8,9,10 in figure..


//function to display reference count and size of freed memory
void display_node(int i)
{
	printf("value=%d\t reference_count=%d freed_size=%d\n",pointer_array[i]->data,pointer_array[i]->ref_count,sizeof(Node));
}

//function to set the pointer points to node and its refrence count.
void set_edge(int so,int dest1,int dest2,int dest3)
{
	if(dest1!=-1)                            
	{
		pointer_array[so]->next_1=pointer_array[dest1];
		pointer_array[dest1]->ref_count+=1;
	}
	if(dest2!=-1)
	{
		pointer_array[so]->next_2=pointer_array[dest2];
		pointer_array[dest2]->ref_count+=1;
	}
	if(dest3!=-1)
	{
		pointer_array[so]->next_3=pointer_array[dest3];
		pointer_array[dest3]->ref_count+=1;
	}
	
}


//function to display all nodes which are present in nodes start from root.
void display_all_nodes(Node* root)
{
	if(root!=NULL)
	{
		printf("value=%d:ref_count=%d\n",root->data,root->ref_count);
	}
	if(root==NULL)
	{
		return;
	}
	display_all_nodes(root->next_1);                   //recursive function
	display_all_nodes(root->next_2);
	display_all_nodes(root->next_3);
}


//display of adjacency list of all nodes.
void adjacency_list()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if(pointer_array[i]!=NULL)
		{
			printf("Value=%d: ",pointer_array[i]->data);
			if(pointer_array[i]->next_1!=NULL)
			{
				printf("%d ->",pointer_array[i]->next_1->data);
			}
			if(pointer_array[i]->next_2!=NULL)
			{
				printf("%d ->",pointer_array[i]->next_2->data);
			}
			if(pointer_array[i]->next_3!=NULL)
			{
				printf("%d ->",pointer_array[i]->next_3->data);
			}
			printf("NULL\n");
		}
	}
}


//function to check node is preent in root or not.
int root_is_present(Node* root1,Node* temp)
{
	if(root1==NULL)
	{
		return 0;
	}
	if(root1->data==temp->data)
	{
		return 1;
	}
	
	if(root_is_present(root1->next_1,temp))
	{
		return 1;
	}
	
	if(root_is_present(root1->next_2,temp))
	{
		return 1;
	}
	if(root_is_present(root1->next_3,temp))
	{
		return 1;
	}
 return 0;
}

//garbage collection using refrence counting mechanism
void garbage_collection_ref_counting(Node* root)
{
	int i=0;
	while(i<8)
	{
		if(root_is_present(root,pointer_array[i])==0 )
		{		
			if(pointer_array[i]->next_1!=NULL)
			{
				pointer_array[i]->next_1->ref_count-=1;
			}
			if(pointer_array[i]->next_2!=NULL)
			{
				pointer_array[i]->next_2->ref_count-=1;
			}
			if(pointer_array[i]->next_3!=NULL)
			{
				pointer_array[i]->next_3->ref_count-=1;
			}
			printf("Garbage:");
			display_node(i);
			free(pointer_array[i]);
			pointer_array[i]=NULL;
		}
		 i++;		
	}
	 
}


//display of adjacency matrix
void adjacency_Matrix()
{
	int adm[8][8];
	int i,j,k;
	
	for(i=0;i<8;i++)	                           	//initialise all indices values to 0
	{
		for(j=0;j<8;j++)
		{
			adm[i][j]=0;
		}	
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			
		if(pointer_array[j]!=NULL&&pointer_array[i]!=NULL)
		{
			
			if(pointer_array[i]->next_1!=NULL)
			{
				if(pointer_array[i]->next_1->data==pointer_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
			if(pointer_array[i]->next_2!=NULL)
			{
				if(pointer_array[i]->next_2->data==pointer_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
			if(pointer_array[i]->next_3!=NULL)
			{
				if(pointer_array[i]->next_3->data==pointer_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
		}
		
		}
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			printf("%d ",adm[i][j]);		              //print the adjacency matrix 
		}
		printf("\n");
	}
}


//mark node with given its attributes.
void mark_the_Nodes(Node*root,int i,int j)
{
    Node *current, *pre;

    current = root;
        
    while (current != NULL) 
    {
  
        if (current->next_1== NULL) 
        {
            current->mark=true;
            current = current->next_2;
        }   
        else 
        {
            pre = current->next_1;
            while ((pre->next_2 != NULL) && (pre->next_2 != current))
            {
            	pre = pre->next_2;
			}
                
            if (pre->next_2 == NULL) 
            {
                pre->next_2 = current;
                current = current->next_1;
            }
            else 
            {
                pre->next_2 = NULL;
                current->mark=true;
                current = current->next_2;
            } 
        }
    }   
    
    current = root;
        
    while (current != NULL) 
    {
  
        if (current->next_1== NULL) 
        {
            current->mark=true;
            current = current->next_3;
        }   
        else 
        {
            pre = current->next_1;
            while ((pre->next_3 != NULL) && (pre->next_3 != current))
            {
            	pre = pre->next_3;
			}
                
            if (pre->next_3 == NULL) 
            {
                pre->next_3 = current;
                current = current->next_1;
            }
            else 
            {
                pre->next_3 = NULL;
                current->mark=true;
                current = current->next_3;
            } 
        }
    }  
    
}


//function to mark with given root
void mark_method(Node* root)
{
	
	if(root!=NULL)
	{
		root->mark=true;
	}
	if(root==NULL)
	{
		return;
	}
	mark_method(root->next_1);
	mark_method(root->next_2);
	mark_method(root->next_3);
}


//function to sweep 
void sweep_method()
{
	int i;
	for(i=0;i<8;i++)
	{
		if(pointer_array[i]->mark==false)
		{
			if(pointer_array[i]->next_1!=NULL)
			{
				pointer_array[i]->next_1->ref_count-=1;
			}
			if(pointer_array[i]->next_2!=NULL)
			{
				pointer_array[i]->next_2->ref_count-=1;
			}
			if(pointer_array[i]->next_3!=NULL)
			{
				pointer_array[i]->next_3->ref_count-=1;
			}
			printf("Garbage:");
			display_node(i);
			free(pointer_array[i]);
			pointer_array[i]=NULL;
		}
	}
}


//driver code
int main()
{
	
	
	//value		
	int val[]={1,2,3,5,7,8,9,10};                //given in assignment
	
	
	int i;
	
	for( i=0;i<8;i++)                                       //Node number  		   	   0,1,2,3,4,5,6,7	points to 1,2,3,5,7,8,9,10 respectively
	{
		Node* newNode =(Node*)malloc(sizeof(Node));
		newNode->data=val[i];
		newNode->next_1=NULL;
		newNode->next_2=NULL;
		newNode->next_3=NULL;
		newNode->ref_count=0;
		newNode->mark=false;		
		pointer_array[i]=newNode;
	}
	
	//setting root1 and root2 ccording to problem
	Node*root1=pointer_array[3];
	pointer_array[3]->ref_count+=1;
	Node*root2=pointer_array[0];
	pointer_array[0]->ref_count+=1;
	
	//setting all nodes from 0 to 7 according to problem
	set_edge(0,1,6,7);
	set_edge(2,5,7,-1);
	set_edge(3,0,-1,-1);
	set_edge(4,0,5,-1);
	set_edge(5,6,-1,-1);
	
	
	printf("\nAll nodes points through Root-1:\n");
	display_all_nodes(root1);
	
		
	printf("\nAll nodes points through Root-2:\n");
	display_all_nodes(root2);
	
	printf("\n\nAdjacency list is  :\n");          //Displaye of Adjacency list of the nodes with corresponding value 
	adjacency_list();
	
	printf("\n\nAdjacency matrix :\n");            //Displayie of Adjacency Matrix of the nodes except root 1 and root 2
	adjacency_Matrix();
	

	
//	printf("\nCalling the mark and sweep garbage collector\n");
//	mark_method(root1);
//	sweep_method();
//	printf("\n\nAdj matrix after removal of garbage:\n");
//	adjacency_Matrix();
	
	
	printf("\nCall to  reference count Garbage collector mechanism\n");
	garbage_collection_ref_counting(root1);
	
	printf("\n\nUpdated Adjacency list after removal of garbage:\n");
	adjacency_list();
	
	printf("\n\nUpdated Adjacency matrix after removal of garbage:\n");
	adjacency_Matrix();
	
}
