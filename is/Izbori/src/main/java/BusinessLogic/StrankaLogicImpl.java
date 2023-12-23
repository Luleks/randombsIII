package BusinessLogic;

import java.util.List;

import Model.Stranka;

import javax.ejb.Remote;
import javax.ejb.Stateless;

import javax.persistence.TypedQuery;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

@Stateless
@Remote(StrankaLogic.class)
public class StrankaLogicImpl implements StrankaLogic {

	private EntityManager em;
	
	public StrankaLogicImpl() {
		EntityManagerFactory emf = Persistence.createEntityManagerFactory("IzboriPU");
		em = emf.createEntityManager();
	}
	
	@Override
	public boolean addStranka(String Naziv, String NosilacListe, int SkupljeniPotpisi, int BrojClanova) {
		try {
			if (SkupljeniPotpisi < 10000)
				return false;
			em.getTransaction().begin();
			Stranka stranka = new Stranka(Naziv, NosilacListe, SkupljeniPotpisi, BrojClanova);
			em.persist(stranka);
			em.getTransaction().commit();
			return true;
		}
		catch (Exception e) {
			return false;
		}
	}

	@Override
	public boolean removeStranka(int id) {
		try {
			Stranka stranka = em.find(Stranka.class, id);
			em.getTransaction().begin();
			em.remove(stranka);
			em.getTransaction().commit();
			return true;
		}
		catch (Exception e) {
			return false;
		}
	}

	@Override
	public Stranka getStranka(int id) {
		try {
			Stranka stranka = em.find(Stranka.class, id);
			return stranka;
		}
		catch (Exception e) {
			return null;
		}
	}

	@Override
	public List<Stranka> getStranke() {
		TypedQuery<Stranka>query = em.createQuery("SELECT s FROM Stranka s", Stranka.class);
		List<Stranka> stranke = query.getResultList();
		return stranke;
	}
	
	@Override
	public List<Integer> getStrankaIds() {
		TypedQuery<Integer>query = em.createQuery("SELECT s.ID FROM Stranka s", Integer.class);
		List<Integer> stranke = query.getResultList();
		return stranke;	
	}

	@Override
	public boolean dodajPotpis(int id) {
		Stranka stranka = getStranka(id);
		if (stranka == null) {
			return false;
		}
		stranka.setSkupljeniPotpisi(stranka.getSkupljeniPotpisi() + 1);
		return true;
	}
}
