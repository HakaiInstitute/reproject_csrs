import csrspy
import pytest


def test_create_transformer():
    t = csrspy.CSRSTransformer(
        s_ref_frame="itrf14",
        s_crs="EPSG:32610",
        s_epoch=2019.500,
        t_epoch=1997.000,
        t_vd="cgg2013a",
        out="utm10")

    assert isinstance(t, csrspy.CSRSTransformer)


def test_forward_call():
    t = csrspy.CSRSTransformer(
        s_ref_frame="itrf14",
        s_crs="EPSG:32610",
        s_epoch=2019.500,
        t_epoch=1997.000,
        t_vd="cgg2013a",
        out="utm10")

    in_coords = (408125.360, 5635102.830, 2170.790)
    out_coords = t.forward(*in_coords)

    assert pytest.approx(out_coords, abs=1e-3) == (408126.755, 5635102.430, 2183.572)


def test_backward_call():
    t = csrspy.CSRSTransformer(
        s_ref_frame="itrf14",
        s_crs="EPSG:32610",
        s_epoch=2019.500,
        t_epoch=1997.000,
        t_vd="cgg2013a",
        out="utm10")

    in_coords = (408126.755, 5635102.430, 2183.572)
    out_coords = t.backward(*in_coords)

    assert pytest.approx(out_coords, abs=1e-3) == (408125.360, 5635102.830, 2170.790)


def test_height_conversion():
    wgs_2_csrs_cgg2013a = csrspy.CSRSTransformer(
        s_ref_frame="itrf14",
        s_crs="EPSG:4326",
        s_epoch=1997.0,
        t_vd="cgg2013a",
        out="utm10")

    wgs_2_csrs_ht2 = csrspy.CSRSTransformer(
        s_ref_frame="itrf14",
        s_crs="EPSG:4326",
        s_epoch=1997.0,
        t_vd="ht2_2010v70",
        out="utm10")

    in_coords = (470880.320, 5381676.930, 19.330)
    out_coords = wgs_2_csrs_ht2.forward(*wgs_2_csrs_cgg2013a.backward(*in_coords))

    assert pytest.approx(out_coords, abs=1e-3) == (470880.320, 5381676.930, 19.198)
