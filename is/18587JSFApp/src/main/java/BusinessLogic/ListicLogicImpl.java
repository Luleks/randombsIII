package BusinessLogic;

import Model.Stranka;
import Model.Glasac;
import Model.GlasackiListic;

import java.util.List;

import javax.ejb.EJB;
import javax.ejb.Stateless;

import javax.persistence.TypedQuery;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

@Stateless
public class ListicLogicImpl implements ListicLogic {
	
	@PersistenceContext(name="IzboriPU")
	private EntityManager em;
	
	@EJB
	private StrankaLogic sli;

	@EJB
	private GlasacLogic gli;
	
	@Override
	public boolean removeListic(int listicID) {
		try {
			GlasackiListic listic = em.find(GlasackiListic.class, listicID);
			em.remove(listic);
			return true;
		}
		catch (Exception e) {
			return false;
		}
	}
	
	@Override
	public List<GlasackiListic> getListici() {
		TypedQuery<GlasackiListic>query = em.createQuery("SELECT l FROM GlasackiListic l", GlasackiListic.class);
		List<GlasackiListic> listici = query.getResultList();
		return listici;
	}
	
	@Override
	public boolean dodajListic(String nazivStranke, String glasacJmbg) {
		try {
			Glasac g = gli.getGlasacByJmbg(glasacJmbg);
			if (g == null || g.isGlasao())
				return false;
			g.setGlasao(true);
			
			GlasackiListic listic = null;
			Stranka stranka = sli.getStrankaByNaziv(nazivStranke);
			if (stranka == null)
				listic = new GlasackiListic(0);
			else
				listic = new GlasackiListic(stranka.getID());
			em.persist(listic);
			return true;
		}
		catch (Exception ec) {
			return false;
		}
	}

	@Override
	public boolean dodajListic(int brStranke, String glasacJmbg) {
		try {
			Glasac g = gli.getGlasacByJmbg(glasacJmbg);
			if (g == null || g.isGlasao())
				return false;
			g.setGlasao(true);
			
			GlasackiListic listic = null;
			Stranka stranka = sli.getStranka(brStranke);
			if (stranka == null)
				listic = new GlasackiListic(0);
			else
				listic = new GlasackiListic(brStranke);
			em.persist(listic);
			return true;
		}
		catch (Exception ec) {
			return false;
		}
	}

	@Override
	public double countIzlaznost() {
		TypedQuery<Long> query = em.createQuery("SELECT COUNT(*) FROM GlasackiListic", Long.class);
		Long glasali = query.getSingleResult();
		Long brGlasaca = gli.countGlasaci();
		return (double)glasali / (double)brGlasaca;
	}

	@Override
	public int countGlasovi(int brStranke) {
		TypedQuery<Long> query = em.createQuery("SELECT COUNT(*) FROM GlasackiListic l WHERE l.strankaID=:brStranke", Long.class);
		query.setParameter("brStranke", brStranke);
		Long glasovi = query.getSingleResult();
		return (int)(long)glasovi;
	}

}
