/**
 * sign.java by Brandon Kmiec. Submitted for CSC 152 November 19, 2024.
 * Write a command-line program that takes arguments p, g, g^d, d, and x, and outputs
 *      r and s (all expressed as integers).
 * Followed https://www.geeksforgeeks.org/command-line-arguments-in-java/ for learning command line arguments in Java
 * Followed https://docs.oracle.com/javase/8/docs/api/?java/math/BigInteger.html for information about Java BigInteger class
 */

import java.math.BigInteger;
import java.util.Random;

public class sign {
    public static void main(String[] args) {
        if (args.length != 5) {
            System.out.println("\nImproper Usage");
            System.out.println("Please use: java sign <p> <g> <g^d> <d> <x>");
            System.exit(0);
        } // end if

        BigInteger p = new BigInteger(args[0]);
        BigInteger g = new BigInteger(args[1]);
        BigInteger gd = new BigInteger(args[2]); // Not sure if supposed to be used in sign
        BigInteger d = new BigInteger(args[3]);
        BigInteger x = new BigInteger(args[4]);

        BigInteger pSub1 = p.subtract(BigInteger.valueOf(1));

        int numBits = p.bitLength();
        Random random = new Random();

        BigInteger e = genRandE(random, numBits, pSub1);

        BigInteger r = calcR(g, e, p);
        BigInteger s = calcS(x, d, r, e, pSub1);

        System.out.println(r);
        System.out.println(s);
    } // end main

    /**
     * Calculate r: g^e mod p
     * @param g generator
     * @param e random prime
     * @param p prime modulus
     * @return g^e mod p
     */
    private static BigInteger calcR(BigInteger g, BigInteger e, BigInteger p) {
        /*
        BigInteger r = g.pow(e.intValue());
        r = r.mod(p);
        return r;
        */
        return (g.pow(e.intValue())).mod(p);
    } // end calR

    /**
     * Calculate s: (x-dr)*(e^-1) mod p-1
     * @param x message
     * @param d private key
     * @param r first part of the signature
     * @param e random prime
     * @param pSub1 p-1 modulus
     * @return (x-dr)*(e^-1) mod p-1
     */
    private static BigInteger calcS(BigInteger x, BigInteger d, BigInteger r, BigInteger e, BigInteger pSub1) {
        /*
        BigInteger s = x.subtract(d.multiply(r));
        s = s.multiply(e.modInverse(pSub1));
        s = s.mod(pSub1);
        return s;
        */
        return ((x.subtract(d.multiply(r))).multiply(e.modInverse(pSub1))).mod(pSub1);
    } // end calcS

    /**
     * Generate a random e where 0<e<p such that gcd(e, p-1) = 1
     * @param random random object used to generate random numbers
     * @param numBits number of bits in p
     * @param pSub1 p-1 modulus
     * @return Random e: 0<e<p such that gcd(e, p-1) = 1
     */
    private static BigInteger genRandE(Random random, int numBits, BigInteger pSub1) {
        BigInteger e = BigInteger.probablePrime(numBits, random);
        while (!e.gcd(pSub1).equals(BigInteger.valueOf(1)) && e.compareTo(BigInteger.ZERO) > 0 &&
                e.compareTo(pSub1.add(BigInteger.ONE)) < 0) {
            e = BigInteger.probablePrime(numBits, random);
        } // end while

        return e;
    } // end genRandE
} // end sign
