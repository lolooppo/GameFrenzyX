import pytest
from src.backend.reservables.CapacityReservable import CapacityReservable
from src.backend.reservables.PeriodReservable import PeriodReservable
from src.backend.reservables.MatchTypeReservable import MatchTypeReservable
from src.backend.reservations.ReservationRequest import ReservationRequest

# The project code defines PricingService under src.backend.reservations in your paste,
# so import that exact class:
from src.backend.reservations.PricingService import PricingService


def test_capacity_reservable_basic_flow():
    r = CapacityReservable("Pool001", "swimming", True, 10, 5.0)
    # Initially available for 3 tickets
    req = ReservationRequest(user_name="u1", date="2025-10-01", ticket_count=3)
    assert r.is_available_for_reservation(req) is True

    # Reserve 3 tickets
    r.reserve(req)
    assert r.current_capacity == 3

    # Now available for 6 more, not for 8
    req2 = ReservationRequest(user_name="u2", date="2025-10-01", ticket_count=6)
    assert r.is_available_for_reservation(req2) is True
    req3 = ReservationRequest(user_name="u3", date="2025-10-01", ticket_count=8)
    assert r.is_available_for_reservation(req3) is False

    # Unreserve 3 tickets
    r.unreserve(req)
    assert r.current_capacity == 0

    # Reset
    r.reserve(ReservationRequest(user_name="u4", date="2025-10-01", ticket_count=2))
    r.reset()
    assert r.current_capacity == 0


def test_period_reservable_slot_reserve_and_overlap():
    pr = PeriodReservable(name="Court A", category="sports", status=True, morning_hourly_rate=50, night_hourly_rate=80)

    # Reserve from hour 9 to 11 (9 and 10 slots)
    req = ReservationRequest(user_name="u1", date="2025-10-01", start_time=9, end_time=11)
    assert pr.is_available_for_reservation(req) is True

    pr.reserve(req)
    # now overlapping request should be denied
    overlap_req = ReservationRequest(user_name="u2", date="2025-10-01", start_time=10, end_time=12)
    assert pr.is_available_for_reservation(overlap_req) is False

    # a non-overlapping adjacent slot (11-12) should be allowed
    adjacent_req = ReservationRequest(user_name="u3", date="2025-10-01", start_time=11, end_time=12)
    assert pr.is_available_for_reservation(adjacent_req) is True

    # unreserve original and re-check
    pr.unreserve(req)
    assert pr.is_available_for_reservation(overlap_req) is True

    # reset clears all
    pr.reserve(req)
    pr.reset()
    for val in pr.periods:
        assert val == 0


def test_matchtype_reservable_toggle_and_pricing_flags():
    mr = MatchTypeReservable(name="Table 1", category="games", status=True, single_match_rate=10.0, multy_match_rate=18.0)
    req = ReservationRequest(user_name="u1", date="2025-10-01", is_single=True)

    # initially available
    assert mr.is_available_for_reservation(req) is True

    # reserve toggles availability off
    mr.reserve(req)
    assert mr.is_available_for_reservation(req) is False

    # unreserve toggles it back on
    mr.unreserve(req)
    assert mr.is_available_for_reservation(req) is True

    # check pricing values returned by pricing service in match case via ReservationRequest flag
    # (PricingService will be tested in separate tests below)


def test_pricing_service_period_rates_morning_and_night():
    # Use a PeriodReservable with known rates
    pr = PeriodReservable(name="Court B", category="sports", status=True, morning_hourly_rate=50.0, night_hourly_rate=80.0)

    # Build a request that covers 2 hours in the morning (9 -> 11)
    req_morning = ReservationRequest(user_name="u1", date="2025-10-01", start_time=9, end_time=11)
    # PricingService in your code expects attributes start_date/end_date (names differ),
    # so set them here to match the service's expectations (integers representing hours).
    req_morning.start_date = req_morning.start_time
    req_morning.end_date = req_morning.end_time

    total_morning = PricingService.total(pr, req_morning)
    assert total_morning == pytest.approx(50.0 * 2)

    # Night example: 19 -> 21 (2 hours)
    req_night = ReservationRequest(user_name="u2", date="2025-10-01", start_time=19, end_time=21)
    req_night.start_date = req_night.start_time
    req_night.end_date = req_night.end_time

    total_night = PricingService.total(pr, req_night)
    assert total_night == pytest.approx(80.0 * 2)


def test_pricing_service_capacity_and_match_pricing():
    # Capacity pricing
    cr = CapacityReservable(name="Pool", category="leisure", status=True, max_capacity=10, ticket_price=5.0)
    req_capacity = ReservationRequest(user_name="u1", date="2025-10-01", ticket_count=4)
    total_capacity = PricingService.total(cr, req_capacity)
    assert total_capacity == pytest.approx(4 * 5.0)

    # Match pricing (single and multi)
    mr_single = MatchTypeReservable(name="Table 2", category="games", status=True, single_match_rate=12.0, multy_match_rate=20.0)
    req_single = ReservationRequest(user_name="u2", date="2025-10-01", is_single=True)
    total_single = PricingService.total(mr_single, req_single)
    assert total_single == pytest.approx(12.0)

    req_multi = ReservationRequest(user_name="u3", date="2025-10-01", is_single=False)
    total_multi = PricingService.total(mr_single, req_multi)
    assert total_multi == pytest.approx(20.0)
