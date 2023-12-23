package tests;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.*;

import Model.Stranka;
import Model.Glasac;

import BusinessLogic.StrankaLogicImpl;
import BusinessLogic.GlasacLogicImpl;
import BusinessLogic.IzboriLogicImpl;
import BusinessLogic.ListicLogicImpl;

public class IzboriTest {
	private static StrankaLogicImpl sli;
	private static GlasacLogicImpl gli;
	private static IzboriLogicImpl ili;
	private static ListicLogicImpl lli;
	
	@BeforeClass
	public static void initTest() {
		sli = new StrankaLogicImpl();
		gli = new GlasacLogicImpl();
		ili = new IzboriLogicImpl();
		lli = new ListicLogicImpl();
		boolean uspesno1 = sli.addStranka("Dummy Stranka 1", "Dummy Politicar 1", 10001, 20);
		boolean uspesno2 = sli.addStranka("Dummy Stranka 2", "Dummy Politicar 2", 12000, 60);
		boolean uspesno3 = sli.addStranka("Dummy Stranka 3", "Dummy Politicar 3", 198000, 40);
		
		assertTrue(uspesno1 && uspesno2 && uspesno3);
		
		uspesno1 = gli.addGlasac("0111111111111", "Luka", "Velickovic", false, false);
		uspesno2 = gli.addGlasac("0222222222222", "Dummmy", "Glasac", true, false);
		uspesno3 = gli.addGlasac("0333333333333", "Dummy1", "Glasac1", false, false);
		boolean uspesno4 = gli.addGlasac("0444444444444", "Dummy2", "Glasac2", false, false);
		
		assertTrue(uspesno1 && uspesno2 && uspesno3 && uspesno4);
		System.out.println("BeforeClass: Inicijalizacija testa uspesna");
	}
	
	@Before
	public void testPrecondition() {

		Stranka s1 = sli.getStranka(1);
		Stranka s2 = sli.getStranka(2);
		Stranka s3 = sli.getStranka(3);
		
		assertNotNull(s1);
		assertNotNull(s2);
		assertNotNull(s3);
		
		Glasac g1 = gli.getGlasacByJmbg("0111111111111");
		Glasac g2 = gli.getGlasacByJmbg("0222222222222");
		Glasac g3 = gli.getGlasacByJmbg("0333333333333");
		Glasac g4 = gli.getGlasacByJmbg("0444444444444");
		
		assertNotNull(g1);
		assertNotNull(g2);
		assertNotNull(g3);
		assertNotNull(g4);

		System.out.println("Before: U sistemu postoje stranke i glasaci");
	}
	
	@Test
	public void test() {
		boolean uspesno1 = lli.dodajListic(1, "0111111111111");
		//boolean neuspesno1 = !lli.dodajListic(0, "011111111111");
		boolean uspesno2 = lli.dodajListic(5, "0222222222222");
		boolean uspesno3 = lli.dodajListic(2, "0333333333333");
		boolean uspesno4 = lli.dodajListic(2, "0444444444444");
		
		assertTrue(uspesno1 && uspesno2 && uspesno3 && uspesno4);		

		Stranka pobednik = ili.proglasiPobednika();
		Stranka pobedio = sli.getStranka(1);
		
		assertEquals("Pogresan pobednik", pobednik, pobedio);
	}
	
	@After
	public void testPostcondition() {
		double izlaznost = lli.countIzlaznost();
		assertTrue(izlaznost == 1.0);
		
		System.out.println("After: Izlaznost je 100%");
	}
	
	@AfterClass
	public static void clearTest() {
		Stranka s1 = sli.getStranka(1);
		Stranka s2 = sli.getStranka(2);
		Stranka s3 = sli.getStranka(3);
		
		Glasac g1 = gli.getGlasacByJmbg("0111111111111");
		Glasac g2 = gli.getGlasacByJmbg("0222222222222");
		Glasac g3 = gli.getGlasacByJmbg("0333333333333");
		Glasac g4 = gli.getGlasacByJmbg("0444444444444");	
		
		sli.removeStranka(s1.getID());
		sli.removeStranka(s2.getID());
		sli.removeStranka(s3.getID());
		gli.removeGlasac(g1.getID());
		gli.removeGlasac(g2.getID());
		gli.removeGlasac(g3.getID());
		gli.removeGlasac(g4.getID());
		
		s1 = sli.getStranka(0);
		s2 = sli.getStranka(1);
		s3 = sli.getStranka(2);
		
		g1 = gli.getGlasacByJmbg("0111111111111");
		g2 = gli.getGlasacByJmbg("0222222222222");
		g3 = gli.getGlasacByJmbg("0333333333333");
		g4 = gli.getGlasacByJmbg("0444444444444");	
		
		assertNull(s1);
		assertNull(s2);
		assertNull(s3);
		
		assertNull(g1);
		assertNull(g2);
		assertNull(g3);
		assertNull(g4);
		
		System.out.println("Baza vracena u originalno stanje");
	}
	

}
