package Controllers;

import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;

import BusinessLogic.IzboriLogic;
import Model.Stranka;

@ManagedBean
@ViewScoped
public class IzboriController {
    
    @EJB
    private IzboriLogic izboriLogic;

    public IzboriController() {

    }

    public Stranka proglasiPobednika() {
        return izboriLogic.proglasiPobednika();
    }
}