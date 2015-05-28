DNA Primer Search locates primers in a given DNA sequence finding the 5' - 3' strand and the reverse complement strand.  The program gives the first hit as output for each strand.

Input can be a base pair FASTA (.fa, .fasta) file, or you can copy paste a DNA sequence.

<img src='http://i.imgur.com/k9dnU1j.png' alt='DNA Search' /> <img src='http://i.imgur.com/aSgyKhd.png' alt='Primer Found' />


## Background ##
Primers are short DNA fragments containing sequences complementary to a target region that will be used to duplicate DNA.

DNA is a 2 stranded, double helix that exists of the nucleic acid A, C and T, G base pairs.

The difference between the 2 strands is the way the DNA grows when it is duplicated:

  * 5' end: A nucleic acid strand which terminates at the chemical group attached to the fifth carbon in the sugar-ring.
  * 3' end: A nucleic acid strand which terminates at the Hydroxyl (-OH) chemical group attached to the third carbon in the sugar-ring.

You only need 1 strand to know the other, because DNA is complementary that means that A = T on the other strand , and C = G

```
First strand 5'		A C T G G G C T T T T C C  3'
			| | | | | | | | | | | | |
Second strand 3'	T G A C C C G A A A A G G  5'
```


When DNA splits in two to later duplicate, it needs some kind of start fragment to know how bind the other ACTG to the strand.  This is what is known as a primer.

Suppose you have a long sequence of DNA
```
Piece of DNA:5'	ACTATCTATCCACTACTTTTTTTTTTACTACTATCATCACGACGGCAGCGAGAGCGGAATTTACGGAGCTTGCGCGCGCGCGCGCGCGATACGCGCGAGGCT  3'
									||||||||||||||||||||
Primer will be					3'	<<<---		CTTAAATGCCTCGAACGCGC		5'	
```

Notice the arrow, that is the way the DNA will be growing.

The primer found in this example is
```
Primer 3'  CTTAAATGCCTCGAACGCGC  5'
```

This is reversed to the standard 5' - 3' CGCGCAAGCTCCGTAAATTC (it is just reversed)

The primer of the complementary strand will look like this:
```
Other strand of DNA		 3' ACACACACACC 5'
so the primer will be 	         5' TGTGTGTGTGG 3'   --->>>>>
```

Notice that the DNA strand is now 3' to 5' and that it will grow the other direction (visually) so the product length are the pieces of the DNA to the right of the primer
and with the original primer to the left.