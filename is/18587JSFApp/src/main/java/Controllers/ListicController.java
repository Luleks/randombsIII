package Controllers;

import java.util.List;

import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;

import BusinessLogic.ListicLogic;
import Model.GlasackiListic;

@ManagedBean
@ViewScoped
public class ListicController {
    private int brStranke;
    private String nazivStranke;
    private String glasacJmbg;

    @EJB
    private ListicLogic listicLogic;

    public ListicController() {

    }

    public int getBrStranke() {
        return brStranke;
    }

    public void setBrStranke(int brStranke) {
        this.brStranke = brStranke;
    }

    public String getNazivStranke() {
        return nazivStranke;
    }

    public void setNazivStranke(String nazivStranke) {
        this.nazivStranke = nazivStranke;
    }

    public String getGlasacJmbg() {
        return glasacJmbg;
    }

    public void setGlasacJmbg(String glasacJmbg) {
        this.glasacJmbg = glasacJmbg;
    }

    public void dodajListic() {
        if (brStranke == 0) {
            listicLogic.dodajListic(brStranke, glasacJmbg);
        } else {
            listicLogic.dodajListic(nazivStranke, glasacJmbg);
        }
    }

    public double countIzlaznost() {
        return listicLogic.countIzlaznost();
    }

    public int countGlasovi() {
        return listicLogic.countGlasovi(brStranke);
    }

    public void removeListic(int listicID) {
        listicLogic.removeListic(listicID);
    }

    public List<GlasackiListic> getListici() {
        return listicLogic.getListici();
    }
}