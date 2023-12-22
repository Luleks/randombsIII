package BusinessLogic;

import Model.Stranka;
import java.util.ArrayList;

public interface StrankaLogic {
	public boolean addStranka(String Naziv, String NosilacListe, int SkupljeniPotpisi, int BrojClanova);
	public boolean removeStranka(int id);
	public Stranka getStranka(int id);
	public ArrayList<Stranka> getStranke();
	public boolean dodajPotpis(int id);
	public int countGlasovi();
}
