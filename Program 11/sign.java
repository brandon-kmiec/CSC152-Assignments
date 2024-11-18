/**
 * sign.java by Brandon Kmiec. Submitted for CSC 152 November 19, 2024.
 * Write a command-line program that takes arguments p, g, g^d, d, and x, and outputs
 *      r and s (all expressed as integers).
 *
 */

import java.math.BigInteger;
import java.util.Random;

public class sign {
    public static void main(String[] args) {
        if (args.length != 6) {
            System.out.println("Improper Usage");
            System.out.println("Please use: sign <p> <g> <g^d> <d> <x>");
            System.exit(0);
        } // end if

        BigInteger p = new BigInteger(args[1]);
        BigInteger g = new BigInteger(args[2]);
        BigInteger gd = new BigInteger(args[3]);
        BigInteger d = new BigInteger(args[4]);
        BigInteger x = new BigInteger(args[5]);

        BigInteger pSub1 = p.subtract(BigInteger.valueOf(1));

        int numBits = p.bitLength();
        Random random = new Random();

        // TODO: put in method "genRandE", remove calcGCD method
        BigInteger e = BigInteger.probablePrime(numBits, random);
        while (!e.gcd(pSub1).equals(BigInteger.valueOf(1))) {
            e = BigInteger.probablePrime(numBits, random);
        } // end while

        BigInteger eMultiInv = e.modInverse(p); // might need to be pSub1 instead of p

        BigInteger r = calcR(g, e);
        BigInteger s = calcS(x, d, r, e, eMultiInv);

        System.out.println(r);
        System.out.println(s);
    } // end main

    /**
     *
     * @return
     */
    private static BigInteger calcR(BigInteger g, BigInteger e) {
        return ;
    } // end calR

    /**
     *
     * @return
     */
    private static BigInteger calcS(BigInteger x, BigInteger d, BigInteger r, BigInteger e, BigInteger eMultiInv) {
        return ;
    } // end calcS

    /**
     *
     * @return
     */
    private static BigInteger calcGCD(BigInteger e, BigInteger p) {
        BigInteger t;
        while (!p.equals(BigInteger.valueOf(0))) {
            t = p;
            p = e.
            p = e % p;
            e = t;
        }
        return ;
    } // end calcGCD

    /**
     *
     * @param numBits
     * @return
     */
    private static BigInteger genRandE(BigInteger numBits) {
        return ;
    } // end genRandE
} // end sign
