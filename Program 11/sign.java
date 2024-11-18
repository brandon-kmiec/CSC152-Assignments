/**
 * sign.java by Brandon Kmiec. Submitted for CSC 152 November 19, 2024.
 * Write a command-line program that takes arguments p, g, g^d, d, and x, and outputs
 *      r and s (all expressed as integers).
 * Followed https://www.geeksforgeeks.org/command-line-arguments-in-java/ for learning command line arguments in
 *
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
        BigInteger gd = new BigInteger(args[2]);
        BigInteger d = new BigInteger(args[3]);
        BigInteger x = new BigInteger(args[4]);

        BigInteger pSub1 = p.subtract(BigInteger.valueOf(1));

        int numBits = p.bitLength();
        Random random = new Random();

        BigInteger e = genRandE(random, numBits, pSub1);
        // TODO: put in method "genRandE", remove calcGCD method


        BigInteger eMultiInv = e.modInverse(p); // might need to be pSub1 instead of p

        BigInteger r = calcR(g, e, p);
        BigInteger s = calcS(x, d, r, e, eMultiInv, pSub1);

        System.out.println(r);
        System.out.println(s);
    } // end main

    /**
     *
     * @param g
     * @param e
     * @param p
     * @return
     */
    private static BigInteger calcR(BigInteger g, BigInteger e, BigInteger p) {
        BigInteger r = g.pow(e.intValue());
        r = r.mod(p);
        return r;
    } // end calR

    /**
     *
     * @param x
     * @param d
     * @param r
     * @param e
     * @param eMultiInv
     * @param pSub1
     * @return
     */
    private static BigInteger calcS(BigInteger x, BigInteger d, BigInteger r, BigInteger e, BigInteger eMultiInv, BigInteger pSub1) {
        BigInteger s = x.subtract(d.multiply(r));
        s = s.multiply(eMultiInv);
        s = s.mod(pSub1);
        return s;
    } // end calcS

    /**
     *
     * @param random
     * @param numBits
     * @param pSub1
     * @return
     */
    private static BigInteger genRandE(Random random, int numBits, BigInteger pSub1) {
        BigInteger e = BigInteger.probablePrime(numBits, random);
        while (!e.gcd(pSub1).equals(BigInteger.valueOf(1))) {
            e = BigInteger.probablePrime(numBits, random);
        } // end while

        return e;
    } // end genRandE
} // end sign
