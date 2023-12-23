package BusinessLogic;

import java.util.List;

import Model.Glasac;

import javax.ejb.Stateless;

import javax.persistence.TypedQuery;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;


@Stateless
public class GlasacLogicImpl implements GlasacLogic {

	@PersistenceContext(name="IzboriPU")
	private EntityManager em;
	
	@Override
	public boolean addGlasac(String Jmbg, String Ime, String Prezime, boolean Funkcioner, boolean Glasao) {
		try {
			em.getTransaction().begin();
			Glasac glasac = new Glasac(Jmbg, Ime, Prezime, Funkcioner, Glasao);
			em.persist(glasac);
			em.getTransaction().commit();
			return true;
		}
		catch (Exception e) {
			return false;
		}
	}

	@Override
	public boolean updateGlasao(int id) {
		Glasac glasac = getGlasac(id);
		if (glasac == null || glasac.isGlasao()) {
			return false;
		}
		glasac.setGlasao(true);
		return true;
	}

	@Override
	public boolean removeGlasac(int id) {
		try {
			Glasac glasac = em.find(Glasac.class, id);
			em.getTransaction().begin();
			em.remove(glasac);
			em.getTransaction().commit();
			return true;
		}
		catch (Exception e) {
			return false;
		}
	}

	@Override
	public Glasac getGlasac(int id) {
		try {
			Glasac glasac = em.find(Glasac.class, id);
			return glasac;
		}
		catch (Exception e) {
			return null;
		}
	}
	
	@Override
	public Glasac getGlasacByJmbg(String jmbg) {
		try {
			TypedQuery<Glasac>query = em.createQuery("SELECT g FROM Glasac g WHERE g.jmbg=:Jmbg", Glasac.class);
			query.setParameter("Jmbg", jmbg);
			Glasac glasac = query.getSingleResult();
			return glasac;
		}
		catch (Exception e) {
			return null;
		}
	}

	@Override
	public List<Glasac> getGlasaci() {
		TypedQuery<Glasac>query = em.createQuery("SELECT g FROM Glasac g", Glasac.class);
		List<Glasac> glasaci = query.getResultList();
		return glasaci;
	}

	@Override
	public Long countGlasaci() {
		TypedQuery<Long> query = em.createQuery("SELECT COUNT(*) FROM Glasac", Long.class);
		Long count = query.getSingleResult();
		return count;
	}
}
