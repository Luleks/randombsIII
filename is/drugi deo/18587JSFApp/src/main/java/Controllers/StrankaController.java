package Controllers;

import java.util.List;
import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ViewScoped;
import Model.Stranka;
import BusinessLogic.StrankaLogic;

@ManagedBean
@ViewScoped
public class StrankaController {

    private int id;
    private String naziv;
    private String nosilacListe;
    private int skupljeniPotpisi;
    private int brojClanova;

    @EJB
    private StrankaLogic strankaLogic;

    public StrankaController() {
    	
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNaziv() {
        return naziv;
    }

    public void setNaziv(String naziv) {
        this.naziv = naziv;
    }

    public String getNosilacListe() {
        return nosilacListe;
    }

    public void setNosilacListe(String nosilacListe) {
        this.nosilacListe = nosilacListe;
    }

    public int getSkupljeniPotpisi() {
        return skupljeniPotpisi;
    }

    public void setSkupljeniPotpisi(int skupljeniPotpisi) {
        this.skupljeniPotpisi = skupljeniPotpisi;
    }

    public int getBrojClanova() {
        return brojClanova;
    }

    public void setBrojClanova(int brojClanova) {
        this.brojClanova = brojClanova;
    }

    public void addStranka(String naziv, String nosilacListe, int skupljeniPotpisi, int brojClanova) {
    	System.out.println(naziv + nosilacListe + skupljeniPotpisi + brojClanova);
        strankaLogic.addStranka(naziv, nosilacListe, skupljeniPotpisi, brojClanova);
    }

    public void removeStranka(int id) {
        strankaLogic.removeStranka(id);
    }

    public void getStrankaById(int id) {
        Stranka stranka = strankaLogic.getStranka(id);
        this.id = stranka.getID();
        naziv = stranka.getNaziv();
        nosilacListe = stranka.getNosilacListe();
        skupljeniPotpisi = stranka.getSkupljeniPotpisi();
        brojClanova = stranka.getBrojClanova();
    }

    public void getStrankaByNaziv(String naziv) {
        Stranka stranka = strankaLogic.getStrankaByNaziv(naziv);
        id = stranka.getID();
        this.naziv = stranka.getNaziv();
        nosilacListe = stranka.getNosilacListe();
        skupljeniPotpisi = stranka.getSkupljeniPotpisi();
        brojClanova = stranka.getBrojClanova();
    }

    public List<Stranka> getStranke() {
        return strankaLogic.getStranke();
    }

    public List<Integer> getStrankaIds() {
        return strankaLogic.getStrankaIds();
    }

    public void dodajPotpis(int id) {
        strankaLogic.dodajPotpis(id);
    }
}