package Stat;

use List::Util qw(sum max min);

sub new{
	my ($type) = shift;
	my ($self) = [];
	
	if(@_){ 					#Instance constructor
		$self = shift;
		return bless $self, $type;
	}
	elsif(ref $type){		#Copy constructor
		return bless [$self], 'Stat';	
	}
	else{						#Empty constructor
		return bless [], 'Stat';
	}
}

sub Mean{
	my($self) = shift;

	return sum(@$self) / scalar(@$self);
}

sub Median{
	my($self) = shift;
	
	my ($odd) = @$self % 2;
	my ($mid) = int(@$self/2);
	
	my (@sorted) = @{$self->Sorted()};
	
	return $odd ? $sorted[$mid] : ($sorted[$mid] + $sorted[$mid - 1])/2;
}

sub Mode{
	my($self) = shift;
	
	my (%mode, @sorted);
	
	
	$mode{$_}++ foreach(@$self);
	
	@sorted = sort{$mode{$b} <=> $mode{$a}} keys %mode;
	
	return $sorted[0];
}

sub Range{
	my($self) = shift;
	
	return max(@$self) - min(@$self);
}

sub Variance{
	my($self) = shift;
	my($sum) = 0;
	
	$mean = $self->Mean();
	
	foreach (@$self){
		$sum += ($mean - $_) * ($mean - $_);
	}
	return $sum / scalar(@$self);
}

sub StdDev{
	my($self) = shift;
	return sqrt($self->Variance());
}

sub Sorted{
	my($self) = shift;
	
	return [sort{$a <=> $b} @$self];
}

sub Covariance{
	my($self) = shift;
	my($other) = shift;
	my($selfMean, $otherMean, $size);
	my (@dotProduct, @selfSquared, @otherSquared);
	
	return undef unless scalar(@$self) == scalar (@$other);
	
	$size				= scalar(@$self);
	$selfMean			= $self->Mean();
	$otherMean		= $other->Mean();
	
	@dotProduct		= @{$self->dotProduct($other)};
	
	@selfSquared	= map{$_ * $_} @$self;
	@otherSquared	= map{$_ * $_} @$other;

	$numerator		= (sum(@dotProduct) - $size * $selfMean * $otherMean) ** 2;
	$denominator	= ( sum(@selfSquared) - $size * ($selfMean ** 2)) 
								* ( sum(@otherSquared) - $size * ($otherMean ** 2));
	return $numerator / $denominator;
}

sub R{
	my($self) = shift;
	my($other) = shift;
	
	return sqrt($self->Covariance($other));
}

sub dotProduct{
	my($self) = shift;
	my($other) = shift;
	
	my($size) = scalar(@$self);
	my(@result);
	
	for(0 .. $size -1){
		push(@result, $other->[$_] * $self->[$_]);
	}
	
	return [@result];
}

1;