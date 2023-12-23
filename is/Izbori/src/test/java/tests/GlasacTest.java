package tests;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.*;

import Model.Glasac;

import BusinessLogic.GlasacLogicImpl;


public class GlasacTest {
	
	private static GlasacLogicImpl gli;
	private static String jmbg = "0111111111111";
	
	@BeforeClass
	public static void initTest() {
		gli = new GlasacLogicImpl();
		System.out.println("Before class: Inicijalizacija testa uspesna");
	}
	
	@Before
	public void testPrecondition() {
		Glasac glasac = gli.getGlasacByJmbg(jmbg);
		assertNull(glasac);
		System.out.println("Before: Preduslov: Ne postoji glasac sa jmbg-om 0111111111111");
	}
	
	@Test
	public void test() {
		gli.addGlasac(jmbg, "Dummy", "Glasac", true, false);
		Glasac glasac = gli.getGlasacByJmbg(jmbg);
		gli.updateGlasao(glasac.getID());

		System.out.println("Test je zavrsen");
	}
	
	@After
	public void testPostcondition() {
		Glasac glasac = gli.getGlasacByJmbg(jmbg);
		assertNotNull(glasac);
		assertTrue(glasac.isGlasao());
		
		System.out.println("After: Postuslov: Postoji glasac sa jmbg-om 0111111111111 i glasao je");
	}
	
	@AfterClass
	public static void clearTest() {
		Glasac glasac = gli.getGlasacByJmbg(jmbg);
		gli.removeGlasac(glasac.getID());
		
		glasac = gli.getGlasacByJmbg(jmbg);
		assertNull(glasac);
		
		System.out.println("AfterClass: Baza je vracena u prvobitno stanje");
	}

}
