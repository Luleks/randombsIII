package BusinessLogic;

import Model.Glasac;
import java.util.ArrayList;

public interface GlasacLogic {
	public boolean addGlasac(String Jmbg, String Ime, String Prezime, boolean Funkcioner, boolean Glasao);
	public boolean updateGlasao();
	public boolean removeGlasac(int id);
	public Glasac getGlasac(int id);
	public ArrayList<Glasac> getGlasaci();
}
