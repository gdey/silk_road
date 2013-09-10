#!/usr/bin/perl
use v5.12;
use Data::Dumper;

my @r90 = (2,3,7,6,1,0,4,5);
sub gen_array {

   my $length = shift;
   my $l = $length - 1;
   my $s = scalar @_;
   my @a = ();
   my @n = 0 .. $l;
   if ( $s < $l ){
     for ( grep { $_ != $s } @n ){
       #say "-"x$l."-> calling self($length,".join(",",@_).",$_)";
       push @a, gen_array($length,@_,$_)
     }
   } else {
     
     for my $i ( 0 .. ($l-1) ){
       my @b = (@_,$i); 
       my $b = 0;
       my @c = map{ 
          #say '-'x$l.'->['.join(',',@b).'] b[$_]:'.$b[$_]." \$_:$_ == ".$b[$b[$_]];
          $b[$b[$_]] == $_ 
       } @n ;
       $b += $_ for( @c );
       if( $b == $length ) {
         #say 'pushing: $b == $length ['.join(',',@b).']'.Dumper(\@c);
         push @a, \@b;
       }
     }
   }
   #say "Returning: ".Dumper(\@a);
   return @a;

}

my $var_name = $ARGV[0] || die "Need a var name";
my $count = $ARGV[1] || 4;
my @f = gen_array($count);
#  perl -E 'printf("0x%02x%02x%02x\n",155,7,105)'
say "// Generated using: $0 $var_name $count";
say "const tile_maps_type $var_name[][] = {"
say '//DDLLRRUU';
say '//'.join('',reverse((0..($count-1))));
say join( ",\n", @f); 
say '};'
