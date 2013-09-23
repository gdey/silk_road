#!/usr/bin/env perl

use v5.12.0;
use Data::Dumper;

sub combine {
   my $v = shift;
   my $cval = sub {
      return [ $_[1] ] unless defined $_[0];
      return [ grep( { defined } @{$_[0]}),$_[1] ] if ref($_[0]) eq 'ARRAY';
      return [ $_[0],$_[1] ]
   };
   map { $cval->($v,$_) } @_;
}

sub prems_ {
   my ($idxs,@vals) = @_;
   my $s= scalar @vals;
   my $idx = $idxs->[ -1 ];
   my $nlidx = $s-2;
   my $lidx = $s-1;
   my @rvals = ();
   return () unless defined $idx;
   for my $idx1 ( ($idx+1)..$nlidx){
      push @rvals, combine( [ @vals[@$idxs,$idx1] ], @vals[($idx1+1)..$lidx] );
   }
   return @rvals;
}

sub prems {
   
   my @vals = @_;
   my $s= scalar @_;
   my @rvals = ();
   my $nlidx = $s-2;
   my $lidx = $s-1;
   for my $idx ( undef, 0..$nlidx ){
      my $i = defined $idx? $idx+1 : 0;
      push @rvals, combine( [ defined $idx? $vals[$idx] : undef ],@vals[$i..$lidx] );
      for my $idxX ( $idx..$nlidx ){
         push @rvals, prems_([$idx..$idxX],@vals);
      }
      #if( defined $idx ){
      #   for my $idx1 ( ($idx+1)..$nlidx ){
      #      say Dumper([ combine( [ @vals[$idx,$idx1] ], @vals[($idx1+1)..$lidx] )]);
      #      for my $idx2 ( ($idx1+1)..$nlidx ){
      #         say Dumper([ combine( [ @vals[$idx,$idx1,$idx2] ], @vals[($idx1+1)..$lidx] )]);
      #      }
      #   }
      #}
   }
   my %hval = map { join('--',@$_) => $_ } @rvals;
   return sort { scalar(@$a) <=> scalar(@$b) } sort { $a->[0] <=> $b->[0] } values %hval;

}
sub pDumper {
   my %h = (
     'ARRAY' => sub {
         my $r = '[ ';
         my @r = ();
         for my $e ( @_ ){
           push @r, pDumper( $e );
         }
         $r .= join(',',@r).' ]';
         return $r;
     },

   );
   my $r = '';
   for( @_ ){
      my $ref = ref($_);
      if( exists $h{ $ref } ){ 
        $r .= $h{ $ref }->(@$_);
      } else {
        $r .= $_;
      }
   }
   return $r;
}



say pDumper( sort { scalar(@$a) <=> scalar(@$b) }prems(($ARGV[0] || 0)..($ARGV[1]||4)));

#say Dumper([ combine( [], 0..7 ) ]);
#for ( 1..6) {
#say Dumper([ combine( [0,$_], ($_+1)..7 ) ]);
#}
