def list_eqaulize_cells(l):
    """ This function modifies a list to contain equal number of cells in each dimension"""

def get_list_dim_len(l,ndim=0,itemcount=[],recur=0):
    """ Finds the depths and their maximum lengths of a given list  """

    if(isinstance(l,list)):
        if(len(l) > 0):
            for item in l:
                if (isinstance(item,list)):
                    recur+=1
                    ndim,itemcount,recur = get_list_dim_len(item,ndim,itemcount,recur)
                    recur-=1
    print(l,recur)
    return(ndim,itemcount,recur)

# ---------------------------------
def print_list(l):
    """ Prints all the elements of a list """
    if(isinstance(l,list)):
        if(len(l) > 0):
            for item in l:
                print_list(item)
    else:
        print(l)
                
       
    
