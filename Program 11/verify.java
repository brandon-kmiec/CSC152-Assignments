/**
 * verify.java by Brandon Kmiec. Submitted for CSC 152 November 19, 2024.
 * Write a command-line program that takes arguments p, g, g^d, x, r, and s, and outputs
 *      1 if (r, s) is a valid signature for x and 0 otherwise.
 * Followed https://www.geeksforgeeks.org/command-line-arguments-in-java/ for learning command line arguments in Java
 * Followed https://docs.oracle.com/javase/8/docs/api/?java/math/BigInteger.html for information about Java BigInteger class
 */

import java.math.BigInteger;

public class verify {
    public static void main(String[] args) {
        if (args.length != 6) {
            System.out.println("\nImproper Usage");
            System.out.println("Please use: java sign <p> <g> <g^d> <x> <r> <s>");
            System.exit(0);
        } // end if

        BigInteger p = new BigInteger(args[0]);
        BigInteger g = new BigInteger(args[1]);
        BigInteger gd = new BigInteger(args[2]);
        BigInteger x = new BigInteger(args[3]);
        BigInteger r = new BigInteger(args[4]);
        BigInteger s = new BigInteger(args[5]);

        BigInteger left = leftSide(gd, r, s, p);
        BigInteger right = rightSide(g, x, p);

        if (left.equals(right))
            System.out.println(1);
        else
            System.out.println(0);
    } // end main

    /**
     * Calculate the left side: (g^d)^r * r^s mod p
     * @param gd public key
     * @param r first part of the signature
     * @param s second part of the signature
     * @param p prime modulus
     * @return (g^d)^r * r^s mod p
     */
    private static BigInteger leftSide(BigInteger gd, BigInteger r, BigInteger s, BigInteger p) {
        /*
         BigInteger lSide = gd.pow(r.intValue());
         lSide = lSide.multiply(r.pow(s.intValue()));
         lSide = lSide.mod(p);
         return lSide;
        */
        return (gd.pow(r.intValue()).multiply(r.pow(s.intValue()))).mod(p);
    } // end leftSide

    /**
     * Calculate the right side: g^x mod p
     * @param g generator
     * @param x message
     * @param p prime modulus
     * @return g^x mod p
     */
    private static BigInteger rightSide(BigInteger g, BigInteger x, BigInteger p) {
        /*
        BigInteger rSide = g.pow(x.intValue());
        rSide = rSide.mod(p);
        return rSide;
        */
        return (g.pow(x.intValue())).mod(p);
    } // end rightSide
} // end verify
