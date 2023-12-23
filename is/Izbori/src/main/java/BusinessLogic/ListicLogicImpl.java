package BusinessLogic;

import Model.Stranka;
import Model.Glasac;
import Model.GlasackiListic;

import javax.ejb.Remote;
import javax.ejb.Stateless;

import javax.persistence.TypedQuery;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

@Stateless
@Remote(ListicLogic.class)
public class ListicLogicImpl implements ListicLogic {
	
	private EntityManager em;
	private StrankaLogicImpl sli;
	private GlasacLogicImpl gli;
	
	public ListicLogicImpl() {
		EntityManagerFactory emf = Persistence.createEntityManagerFactory("IzboriPU");
		em = emf.createEntityManager();
		
		sli = new StrankaLogicImpl();
		gli = new GlasacLogicImpl();
	}

	@Override
	public boolean dodajListic(int brStranke, String glasacJmbg) {
		try {
			Glasac g = gli.getGlasacByJmbg(glasacJmbg);
			if (g == null || g.isGlasao())
				return false;
			g.setGlasao(true);
			
			em.getTransaction().begin();
			GlasackiListic listic = null;
			Stranka stranka = sli.getStranka(brStranke);
			if (stranka == null)
				listic = new GlasackiListic(-1);
			else
				listic = new GlasackiListic(brStranke);
			em.persist(listic);
			em.getTransaction().commit();
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
		TypedQuery<Long> query = em.createQuery("SELECT COUNT(*) FROM GlasackiListic l WHERE l.izabranaStranka=:brStranke", Long.class);
		query.setParameter("brStranke", brStranke);
		Long glasovi = query.getSingleResult();
		return (int)(long)glasovi;
	}

}
