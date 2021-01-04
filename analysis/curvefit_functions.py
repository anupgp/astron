import numpy as np
# ---------------------------
# Genralized logistic function
def funlogistic(x,top,xmid,steep):
    out = (top / (1+(steep*np.exp(-x*xmid)))) # [top, xmid, steep] f(x) = top/(1+exp(-steepness*(x-xmid)))
    return(out)
# f(x) = top/(1+a*exp(-bx))
# -----------------------------
# staightline fit
def funline(x,slope,yintercept):
    out = ((x*slope) + yintercept)
    return(out)
# ---------------------------
# hill equation
def funhill(x,vmax,kd,coef):
    out = (Vmax * pow(x,coef) / (pow(kd,coeff)+pow(x,coef)))
    return(out)
# --------------------------

